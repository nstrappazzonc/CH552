#include <stdint.h>
#include <stdio.h>
#include "ch552.h"
#include "usb_cdc.h"
#include "utils.h"

void USB_ISR(void) __interrupt(INT_NO_USB) {
  USBInterrupt();
}

void main(void) {
  init();
  USBInit();

  while(1){
    CDC_println("Hello from CH552T with USB");
    delay(1000);
  }
}
