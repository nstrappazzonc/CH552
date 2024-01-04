#include "ch552.h"
#include "usb_handler.h"

volatile uint16_t SetupLen;
volatile uint8_t  SetupReq, UsbConfig;
__code uint8_t *pDescr;

// ===================================================================================
// Fast Copy Function
// ===================================================================================
// Copy descriptor *pDescr to Ep0 using double pointer
// (Thanks to Ralph Doncaster)
#pragma callee_saves USB_EP0_copyDescr
void USB_EP0_copyDescr(uint8_t len) {
  len;                          // stop unreferenced argument warning
  __asm
    push ar7                    ; r7 -> stack
    mov  r7, dpl                ; r7 <- len
    inc  _XBUS_AUX              ; select dptr1
    mov  dptr, #_EP0_buffer     ; dptr1 <- EP0_buffer
    dec  _XBUS_AUX              ; select dptr0
    mov  dpl, _pDescr           ; dptr0 <- *pDescr
    mov  dph, (_pDescr + 1)
    01$:
    clr  a                      ; acc <- #0
    movc a, @a+dptr             ; acc <- *pDescr[dptr0]
    inc  dptr                   ; inc dptr0
    .DB  0xA5                   ; acc -> EP0_buffer[dptr1] & inc dptr1
    djnz r7, 01$                ; repeat len times
    pop  ar7                    ; r7 <- stack
  __endasm;
}

void USB_EP0_SETUP(void) {
  uint8_t len = USB_RX_LEN;
  if(len == (sizeof(USB_SETUP_REQ))) {
    SetupLen = ((uint16_t)USB_setupBuf->wLengthH<<8) | (USB_setupBuf->wLengthL);
    len = 0;                                      // default is success and upload 0 length
    SetupReq = USB_setupBuf->bRequest;

    if( (USB_setupBuf->bRequestType & USB_REQ_TYP_MASK) != USB_REQ_TYP_STANDARD ) {
      len = CDC_control();                // non-standard request
    }

    else {                                        // standard request
      switch(SetupReq) {                          // request ccfType
        case USB_GET_DESCRIPTOR:
          switch(USB_setupBuf->wValueH) {
            case USB_DESCR_TYP_DEVICE:            // Device Descriptor
              pDescr = (uint8_t*)&DevDescr;       // put descriptor into out buffer
              len = sizeof(DevDescr);             // descriptor length
              break;
            case USB_DESCR_TYP_CONFIG:            // Configuration Descriptor
              pDescr = (uint8_t*)&CfgDescr;       // put descriptor into out buffer
              len = sizeof(CfgDescr);             // descriptor length
              break;
            case USB_DESCR_TYP_STRING:
              switch(USB_setupBuf->wValueL) {      // String Descriptor Index
                case 0:   pDescr = USB_STR_DESCR_i0; break;
                case 1:   pDescr = USB_STR_DESCR_i1; break;
                case 2:   pDescr = USB_STR_DESCR_i2; break;
                case 3:   pDescr = USB_STR_DESCR_i3; break;
                case 4:   pDescr = USB_STR_DESCR_i4; break;
                default:  pDescr = USB_STR_DESCR_ix; break;
              }
              len = pDescr[0];                    // descriptor length
              break;

            #ifdef USB_REPORT_DESCR
            case USB_DESCR_TYP_REPORT:
              if(USB_setupBuf->wValueL == 0) {
                pDescr = USB_REPORT_DESCR;
                len = USB_REPORT_DESCR_LEN;
              }
              else len = 0xff;
              break;
            #endif

            default:
              len = 0xff;                         // unsupported descriptors or error
              break;
          }

          if(len != 0xff) {
            if(SetupLen > len) SetupLen = len;    // limit length
            len = SetupLen >= EP0_SIZE ? EP0_SIZE : SetupLen;
            USB_EP0_copyDescr(len);               // copy descriptor to Ep0
            SetupLen -= len;
            pDescr += len;
          }
          break;

        case USB_SET_ADDRESS:
          SetupLen = USB_setupBuf->wValueL;        // save the assigned address
          break;

        case USB_GET_CONFIGURATION:
          EP0_buffer[0] = UsbConfig;
          if (SetupLen >= 1) len = 1;
          break;

        case USB_SET_CONFIGURATION:
          UsbConfig = USB_setupBuf->wValueL;
          break;

        case USB_GET_INTERFACE:
          break;

        case USB_SET_INTERFACE:
          break;

        case USB_CLEAR_FEATURE:
          if( (USB_setupBuf->bRequestType & 0x1F) == USB_REQ_RECIP_DEVICE ) {
            if( ( ( (uint16_t)USB_setupBuf->wValueH << 8 ) | USB_setupBuf->wValueL ) == 0x01 ) {
              if( ((uint8_t*)&CfgDescr)[7] & 0x20) {
                // wake up
              }
              else len = 0xFF;               // failed
            }
            else len = 0xFF;                 // failed
          }
          else if( (USB_setupBuf->bRequestType & USB_REQ_RECIP_MASK) == USB_REQ_RECIP_ENDP ) {
            switch(USB_setupBuf->wIndexL) {
              case 0x82:
                UEP2_CTRL = UEP2_CTRL & ~ ( bUEP_T_TOG | MASK_UEP_T_RES ) | UEP_T_RES_NAK;
                break;
              case 0x02:
                UEP2_CTRL = UEP2_CTRL & ~ ( bUEP_R_TOG | MASK_UEP_R_RES ) | UEP_R_RES_ACK;
                break;
              case 0x81:
                UEP1_CTRL = UEP1_CTRL & ~ ( bUEP_T_TOG | MASK_UEP_T_RES ) | UEP_T_RES_NAK;
                break;
              default:
                len = 0xFF;                 // unsupported endpoint
                break;
            }
          }
          else len = 0xFF;                  // unsupported for non-endpoint
          break;

        case USB_SET_FEATURE:
          if( (USB_setupBuf->bRequestType & 0x1F) == USB_REQ_RECIP_DEVICE ) {
            if( ( ( (uint16_t)USB_setupBuf->wValueH << 8 ) | USB_setupBuf->wValueL ) == 0x01 ) {
              if( !(((uint8_t*)&CfgDescr)[7] & 0x20) ) len = 0xFF;  // failed
            }
            else len = 0xFF;                                        // failed
          }
          else if( (USB_setupBuf->bRequestType & 0x1F) == USB_REQ_RECIP_ENDP ) {
            if( ( ( (uint16_t)USB_setupBuf->wValueH << 8 ) | USB_setupBuf->wValueL ) == 0x00 ) {
              switch( ( (uint16_t)USB_setupBuf->wIndexH << 8 ) | USB_setupBuf->wIndexL ) {
                case 0x82:
                  UEP2_CTRL = UEP2_CTRL & (~bUEP_T_TOG) | UEP_T_RES_STALL;// Set EP2 IN STALL
                  break;
                case 0x81:
                  UEP1_CTRL = UEP1_CTRL & (~bUEP_T_TOG) | UEP_T_RES_STALL;// Set EP1 IN STALL
                  break;
                default:
                  len = 0xFF;               // failed
                  break;
              }
            }
            else len = 0xFF;                // failed
          }
          else len = 0xFF;                  // failed
          break;

        case USB_GET_STATUS:
          EP0_buffer[0] = 0x00;
          EP0_buffer[1] = 0x00;
          if(SetupLen >= 2) len = 2;
          else len = SetupLen;
          break;

        default:
          len = 0xff;                       // failed
          break;
      }
    }
  }
  else len = 0xff;                          // wrong packet length

  if(len == 0xff) {
    SetupReq = 0xFF;
    UEP0_CTRL = bUEP_R_TOG | bUEP_T_TOG | UEP_R_RES_STALL | UEP_T_RES_STALL;//STALL
  }
  else if(len <= EP0_SIZE) {      // Tx data to host or send 0-length packet
    UEP0_T_LEN = len;
    UEP0_CTRL = bUEP_R_TOG | bUEP_T_TOG | UEP_R_RES_ACK | UEP_T_RES_ACK;// Expect DATA1, Answer ACK
  }
  else {
    UEP0_T_LEN = 0;  // Tx data to host or send 0-length packet
    UEP0_CTRL = bUEP_R_TOG | bUEP_T_TOG | UEP_R_RES_ACK | UEP_T_RES_ACK;// Expect DATA1, Answer ACK
  }
}

void USB_EP0_IN(void) {
  uint8_t len;
  switch(SetupReq) {

    case USB_GET_DESCRIPTOR:
      len = SetupLen >= EP0_SIZE ? EP0_SIZE : SetupLen;
      USB_EP0_copyDescr(len);                     // copy descriptor to Ep0
      SetupLen  -= len;
      pDescr    += len;
      UEP0_T_LEN = len;
      UEP0_CTRL ^= bUEP_T_TOG;                    // switch between DATA0 and DATA1
      break;

    case USB_SET_ADDRESS:
      USB_DEV_AD = USB_DEV_AD & bUDA_GP_BIT | SetupLen;
      UEP0_CTRL  = UEP_R_RES_ACK | UEP_T_RES_NAK;
      break;

    default:
      UEP0_T_LEN = 0;                             // end of transaction
      UEP0_CTRL  = UEP_R_RES_ACK | UEP_T_RES_NAK;
      break;
  }
}

void USB_EP0_OUT(void) {
  UEP0_T_LEN = 0;
  UEP0_CTRL |= UEP_R_RES_ACK | UEP_T_RES_NAK;     // respond Nak
}

void USBInterrupt(void) {   // inline not really working in multiple files in SDCC
  if(UIF_TRANSFER) {
    // Dispatch to service functions
    uint8_t callIndex = USB_INT_ST & MASK_UIS_ENDP;
    switch (USB_INT_ST & MASK_UIS_TOKEN) {
      case UIS_TOKEN_OUT:
        switch (callIndex) {
          case 0: CDC_EP0_OUT(); break;
          case 2: CDC_EP2_OUT(); break;
          default: break;
        }
        break;
      case UIS_TOKEN_SOF:
        switch (callIndex) {
          default: break;
        }
        break;
      case UIS_TOKEN_IN:
        switch (callIndex) {
          case 0: USB_EP0_IN(); break;
          case 1: CDC_EP1_IN(); break;
          case 2: CDC_EP2_IN(); break;
          // #ifdef EP3_IN_callback
          // case 3: EP3_IN_callback(); break;
          // #endif
          // #ifdef EP4_IN_callback
          // case 4: EP4_IN_callback(); break;
          // #endif
          default: break;
        }
        break;
      case UIS_TOKEN_SETUP:
        switch (callIndex) {
          case 0: USB_EP0_SETUP(); break;
          default: break;
        }
        break;
    }
    UIF_TRANSFER = 0;                       // clear interrupt flag
  }

  // Device mode USB bus reset
  if(UIF_BUS_RST) {
    UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;

    USBReset();

    USB_DEV_AD   = 0x00;
    UIF_SUSPEND  = 0;
    UIF_TRANSFER = 0;
    UIF_BUS_RST  = 0;                       // clear interrupt flag
  }

  // USB bus suspend / wake up
  if (UIF_SUSPEND) {
    UIF_SUSPEND = 0;
    if ( !(USB_MIS_ST & bUMS_SUSPEND) ) USB_INT_FG = 0xFF;  // clear interrupt flag
  }
}

void USBInit(void) {
  USB_CTRL    = bUC_DEV_PU_EN               // USB internal pull-up enable
              | bUC_INT_BUSY                // Return NAK if USB INT flag not clear
              | bUC_DMA_EN;                 // DMA enable
  UDEV_CTRL   = bUD_PD_DIS                  // Disable UDP/UDM pulldown resistor
              | bUD_PORT_EN;                // Enable port, full-speed

  UEP0_DMA    = (uint16_t)EP0_buffer;       // EP0 data transfer address
  UEP0_CTRL   = UEP_R_RES_ACK               // EP0 Manual flip, OUT transaction returns ACK
              | UEP_T_RES_NAK;              // EP0 IN transaction returns NAK

  UEP1_DMA    = (uint16_t)EP1_buffer;       // EP1 data transfer address
  UEP2_DMA    = (uint16_t)EP2_buffer;       // EP2 data transfer address
  UEP1_CTRL   = bUEP_AUTO_TOG               // EP1 Auto flip sync flag
              | UEP_T_RES_NAK;              // EP1 IN transaction returns NAK
  UEP2_CTRL   = bUEP_AUTO_TOG               // EP2 Auto flip sync flag
              | UEP_T_RES_NAK               // EP2 IN transaction returns NAK
              | UEP_R_RES_ACK;              // EP2 OUT transaction returns ACK
  UEP2_3_MOD  = bUEP2_RX_EN | bUEP2_TX_EN;  // EP2 double buffer (0x0C)
  UEP4_1_MOD  = bUEP1_TX_EN;                // EP1 TX enable (0x40)

  USB_INT_EN |= bUIE_SUSPEND                // Enable device hang interrupt
              | bUIE_TRANSFER               // Enable USB transfer completion interrupt
              | bUIE_BUS_RST;               // Enable device mode USB bus reset interrupt

  USB_INT_FG |= 0x1F;                       // Clear interrupt flag
  IE_USB      = 1;                          // Enable USB interrupt
  EA          = 1;                          // Enable global interrupts

  UEP0_T_LEN  = 0;                          // Must be zero at start
  UEP1_T_LEN  = 0;
  UEP2_T_LEN  = 0;
}
