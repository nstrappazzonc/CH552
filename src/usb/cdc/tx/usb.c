#include <string.h>
#include "ch552.h"
#include "config.h"
#include "usb.h"

volatile uint16_t usb_tx_len;
volatile uint8_t  SetupReq, UsbConfig;
__code uint8_t *p_usb_tx;

// ===================================================================================
// Device Descriptor
// ===================================================================================
__code USB_DEV_DESCR DevDescr = {
  .bLength            = sizeof(DevDescr),       // size of the descriptor in bytes: 18
  .bDescriptorType    = USB_DESCR_TYP_DEVICE,   // device descriptor: 0x01
  .bcdUSB             = 0x0110,                 // USB specification: USB 1.1
  .bDeviceClass       = 0,                      // interface will define class
  .bDeviceSubClass    = 0,                      // unused
  .bDeviceProtocol    = 0,                      // unused
  .bMaxPacketSize0    = EP0_SIZE,               // maximum packet size for Endpoint 0
  .idVendor           = USB_VENDOR_ID,          // VID
  .idProduct          = USB_PRODUCT_ID,         // PID
  .bcdDevice          = USB_DEVICE_VERSION,     // device version
  .iManufacturer      = 1,                      // index of Manufacturer String Descr
  .iProduct           = 2,                      // index of Product String Descriptor
  .iSerialNumber      = 3,                      // index of Serial Number String Descr
  .bNumConfigurations = 1                       // number of possible configurations
};

// ===================================================================================
// Configuration Descriptor
// ===================================================================================
__code USB_CFG_DESCR_CDC CfgDescr = {
  // Configuration Descriptor
  .config = {
    .bLength            = sizeof(USB_CFG_DESCR),  // size of the descriptor in bytes
    .bDescriptorType    = USB_DESCR_TYP_CONFIG,   // configuration descriptor: 0x02
    .wTotalLength       = sizeof(CfgDescr),       // total length in bytes
    .bNumInterfaces     = 2,                      // number of interfaces: 2
    .bConfigurationValue= 1,                      // value to select this configuration
    .iConfiguration     = 0,                      // no configuration string descriptor
    .bmAttributes       = 0x80,                   // attributes = bus powered, no wakeup
    .MaxPower           = USB_MAX_POWER_MA / 2    // in 2mA units
  },
  // Interface Association Descriptor
  .association = {
    .bLength            = sizeof(USB_IAD_DESCR),  // size of the descriptor in bytes
    .bDescriptorType    = USB_DESCR_TYP_IAD,      // interf association descr: 0x0B
    .bFirstInterface    = 0,                      // first interface
    .bInterfaceCount    = 2,                      // total number of interfaces
    .bFunctionClass     = USB_DEV_CLASS_COMM,     // function class: CDC (0x02)
    .bFunctionSubClass  = 2,                      // 2: Abstract Control Model (ACM)
    .bFunctionProtocol  = 1,                      // 1: AT command protocol
    .iFunction          = 4                       // index of String Descriptor
  },
  // Interface Descriptor: Interface 0 (CDC)
  .interface0 = {
    .bLength            = sizeof(USB_ITF_DESCR),  // size of the descriptor in bytes: 9
    .bDescriptorType    = USB_DESCR_TYP_INTERF,   // interface descriptor: 0x04
    .bInterfaceNumber   = 0,                      // number of this interface: 0
    .bAlternateSetting  = 0,                      // value used to select alternative setting
    .bNumEndpoints      = 1,                      // number of endpoints used: 1
    .bInterfaceClass    = USB_DEV_CLASS_COMM,     // interface class: CDC (0x02)
    .bInterfaceSubClass = 2,                      // 2: Abstract Control Model (ACM)
    .bInterfaceProtocol = 1,                      // 1: AT command protocol
    .iInterface         = 4                       // index of String Descriptor
  },
  // Functional Descriptors for Interface 0
  .functional = {
    0x05,0x24,0x00,0x10,0x01,                     // header functional descriptor
    0x05,0x24,0x01,0x00,0x00,                     // call management functional descriptor
    0x04,0x24,0x02,0x02,                          // direct line management functional descriptor
    0x05,0x24,0x06,0x00,0x01                      // union functional descriptor: CDC IF0, Data IF1
  },
  // Endpoint Descriptor: Endpoint 1 (CDC Upload, Interrupt)
  .ep1IN = {
    .bLength            = sizeof(USB_ENDP_DESCR), // size of the descriptor in bytes: 7
    .bDescriptorType    = USB_DESCR_TYP_ENDP,     // endpoint descriptor: 0x05
    .bEndpointAddress   = USB_ENDP_ADDR_EP1_IN,   // endpoint: 1, direction: IN (0x81)
    .bmAttributes       = USB_ENDP_TYPE_INTER,    // transfer type: interrupt (0x03)
    .wMaxPacketSize     = EP1_SIZE,               // max packet size
    .bInterval          = 1                       // polling intervall in ms
  },
  // Interface Descriptor: Interface 1 (Data)
  .interface1 = {
    .bLength            = sizeof(USB_ITF_DESCR),  // size of the descriptor in bytes: 9
    .bDescriptorType    = USB_DESCR_TYP_INTERF,   // interface descriptor: 0x04
    .bInterfaceNumber   = 1,                      // number of this interface: 1
    .bAlternateSetting  = 0,                      // value used to select alternative setting
    .bNumEndpoints      = 2,                      // number of endpoints used: 2
    .bInterfaceClass    = USB_DEV_CLASS_DATA,     // interface class: data (0x0a)
    .bInterfaceSubClass = 0,                      // interface sub class
    .bInterfaceProtocol = 0,                      // interface protocol
    .iInterface         = 4                       // index of String Descriptor
  },
  // Endpoint Descriptor: Endpoint 2 (OUT)
  .ep2OUT = {
    .bLength            = sizeof(USB_ENDP_DESCR), // size of the descriptor in bytes: 7
    .bDescriptorType    = USB_DESCR_TYP_ENDP,     // endpoint descriptor: 0x05
    .bEndpointAddress   = USB_ENDP_ADDR_EP2_OUT,  // endpoint: 2, direction: OUT (0x02)
    .bmAttributes       = USB_ENDP_TYPE_BULK,     // transfer type: bulk (0x02)
    .wMaxPacketSize     = EP2_SIZE,               // max packet size
    .bInterval          = 0                       // polling intervall (ignored for bulk)
  },
  // Endpoint Descriptor: Endpoint 2 (IN)
  .ep2IN = {
    .bLength            = sizeof(USB_ENDP_DESCR), // size of the descriptor in bytes: 7
    .bDescriptorType    = USB_DESCR_TYP_ENDP,     // endpoint descriptor: 0x05
    .bEndpointAddress   = USB_ENDP_ADDR_EP2_IN,   // endpoint: 2, direction: IN (0x82)
    .bmAttributes       = USB_ENDP_TYPE_BULK,     // transfer type: bulk (0x02)
    .wMaxPacketSize     = EP2_SIZE,               // max packet size
    .bInterval          = 0                       // polling intervall (ignored for bulk)
  }
};

// Configure Serial Port
__xdata CDC_LINE_CODING_TYPE CDC_lineCodingB = {
  .baudrate = 115200, // baudrate 115200
  .stopbits = 0,      // 1 stopbit
  .parity   = 0,      // no parity
  .databits = 8       // 8 databits
};

// Manufacturer String Descriptor (Index 1)
__code uint16_t ManufDescr[] = {
  ((uint16_t)USB_DESCR_TYP_STRING << 8) | sizeof(ManufDescr), MANUFACTURER_STR };

// Product String Descriptor (Index 2)
__code uint16_t ProdDescr[] = {
  ((uint16_t)USB_DESCR_TYP_STRING << 8) | sizeof(ProdDescr), PRODUCT_STR };

// Serial String Descriptor (Index 3)
__code uint16_t SerDescr[] = {
  ((uint16_t)USB_DESCR_TYP_STRING << 8) | sizeof(SerDescr), SERIAL_STR };

// Write single character to OUT buffer
void USBWrite(char c) {
  EP2_buffer[EP2_SIZE + UEP2_T_LEN++] = c;
}

// Write string with newline to OUT buffer and flush
void USBWriteString(char* str) {
  UEP2_T_LEN = 0;
  while(*str) USBWrite(*str++);
  UEP2_CTRL = UEP2_CTRL & ~MASK_UEP_T_RES | UEP_T_RES_ACK;
}

void USB_EP2_IN(void) {
  UEP2_T_LEN = 0;
  UEP2_CTRL = UEP2_CTRL & ~MASK_UEP_T_RES | UEP_T_RES_NAK;
}

void USB_EP0_SETUP(void) {
  uint8_t len = 0;
  usb_tx_len = setupBuf->wLengthL;
  SetupReq = setupBuf->bRequest;

  switch(SetupReq) {
    case USB_GET_DESCRIPTOR:
      switch(setupBuf->wValueH) {
        case USB_DESCR_TYP_DEVICE:
          p_usb_tx = (uint8_t*)&DevDescr;
          len = sizeof(DevDescr);
          break;
        case USB_DESCR_TYP_CONFIG:
          p_usb_tx = (uint8_t*)&CfgDescr;
          len = sizeof(CfgDescr);
          break;
        case USB_DESCR_TYP_STRING:
          switch(setupBuf->wValueL) {
            case 1: p_usb_tx = USB_STR_DESCR_i1; break;
            case 2: p_usb_tx = USB_STR_DESCR_i2; break;
            case 3: p_usb_tx = USB_STR_DESCR_i3; break;
          }
          len = setupBuf->wLengthL;
          break;
      }

      if(len) {
        if(usb_tx_len > len) usb_tx_len = len;
        len = MIN(usb_tx_len, EP0_SIZE);
        memcpy(EP0_buffer, p_usb_tx, len);
        usb_tx_len -= len;
        p_usb_tx += len;
      }
      break;

    case USB_SET_ADDRESS:
      usb_tx_len = setupBuf->wValueL;
      break;

    case USB_GET_CONFIGURATION:
      EP0_buffer[0] = UsbConfig;
      UEP0_T_LEN = 1;
      break;

    case USB_SET_CONFIGURATION:
      UsbConfig = setupBuf->wValueL;
      break;

    case USB_GET_STATUS:
      EP0_buffer[0] = 0x00;
      EP0_buffer[1] = 0x00;
      UEP0_T_LEN = 2;
      break;
  }

  UEP0_T_LEN = len;
  UEP0_CTRL = bUEP_R_TOG | bUEP_T_TOG | UEP_R_RES_ACK | UEP_T_RES_ACK;
}

void USB_EP0_IN(void) {
  uint8_t len;
  switch(SetupReq) {
    case USB_GET_DESCRIPTOR:
      len = MIN(usb_tx_len, EP0_SIZE);
      memcpy(EP0_buffer, p_usb_tx, len);
      usb_tx_len  -= len;
      p_usb_tx    += len;
      UEP0_T_LEN = len;
      UEP0_CTRL ^= bUEP_T_TOG;
      break;

    case USB_SET_ADDRESS:
      USB_DEV_AD = USB_DEV_AD & bUDA_GP_BIT | usb_tx_len;
      UEP0_CTRL  = UEP_R_RES_ACK | UEP_T_RES_NAK;
      break;
  }
}

void USBInterrupt(void) {
  if(UIF_TRANSFER) {
    switch (USB_INT_ST & (MASK_UIS_TOKEN | MASK_UIS_ENDP)) {
      case UIS_TOKEN_IN | 0:
        USB_EP0_IN();
        break;

      case UIS_TOKEN_IN | 2:
        USB_EP2_IN();
        break;

      case UIS_TOKEN_SETUP | 0:
        USB_EP0_SETUP();
        break;
    }
    UIF_TRANSFER = 0;
  }

  // Device mode USB bus reset
  if(UIF_BUS_RST) {
    UEP0_CTRL = UEP_R_RES_ACK | UEP_T_RES_NAK;
    UEP1_CTRL = bUEP_AUTO_TOG | UEP_T_RES_NAK;
    UEP2_CTRL = bUEP_AUTO_TOG | UEP_T_RES_NAK | UEP_R_RES_ACK;

    USB_DEV_AD   = 0x00;
    UIF_SUSPEND  = 0;
    UIF_TRANSFER = 0;
    UIF_BUS_RST  = 0;
  }

  // USB bus suspend / wake up
  if (UIF_SUSPEND) {
    UIF_SUSPEND = 0;
    if ( !(USB_MIS_ST & bUMS_SUSPEND) ) USB_INT_FG = 0xFF;  // clear interrupt flag
  }
}

void USBInit(void) {
  USB_CTRL    |= bUC_RESET_SIE | bUC_CLR_ALL;
  USB_CTRL    &= ~bUC_CLR_ALL;

  USB_CTRL    = bUC_DEV_PU_EN               // USB internal pull-up enable
              | bUC_INT_BUSY                // Return NAK if USB INT flag not clear
              | bUC_DMA_EN;                 // DMA enable
  UDEV_CTRL   = bUD_PD_DIS                  // Disable UDP/UDM pulldown resistor
              | bUD_PORT_EN;                // Enable port, full-speed

  UEP0_DMA    = EP0_ADDR;
  UEP0_CTRL   = UEP_R_RES_ACK               // EP0 Manual flip, OUT transaction returns ACK
              | UEP_T_RES_NAK;              // EP0 IN transaction returns NAK

  UEP2_DMA    = EP2_ADDR;                   // EP2 data transfer address
  UEP2_CTRL   = bUEP_AUTO_TOG               // EP2 Auto flip sync flag
              | UEP_T_RES_NAK               // EP2 IN transaction returns NAK
              | UEP_R_RES_ACK;              // EP2 OUT transaction returns ACK
  UEP2_3_MOD  = bUEP2_RX_EN | bUEP2_TX_EN;  // EP2 double buffer (0x0C)

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
