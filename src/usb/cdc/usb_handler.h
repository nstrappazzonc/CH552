#include <stdint.h>
#include "usb_descr.h"

// ===================================================================================
// Variables
// ===================================================================================
#define USB_setupBuf ((PUSB_SETUP_REQ)EP0_buffer)
extern volatile uint8_t  SetupReq;
extern volatile uint16_t SetupLen;

// ===================================================================================
// Custom External USB Handler Functions
// ===================================================================================
uint8_t CDC_control(void);
void CDC_setup(void);
void CDC_reset(void);
void CDC_EP0_OUT(void);
void CDC_EP1_IN(void);
void CDC_EP2_IN(void);
void CDC_EP2_OUT(void);

// ===================================================================================
// Functions
// ===================================================================================
void USBInterrupt(void);
void USBInit(void);
