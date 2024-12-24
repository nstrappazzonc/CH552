#include <stdint.h>
#include <stdio.h>
#include "ch552.h"
#include "usb.h"
#include "utils.h"

void USBInit(void);
void USBInterrupt(void);
void USB_ISR(void) __interrupt(INT_NO_USB) {
  USBInterrupt();
}

void main(void) {
  init();
  USBInit();

  int counter = 0;
  char buffer[32];

  while(1){
    sprintf(buffer, "%d - Hello from CH552G with USB\n", counter++);

    USBWriteString(buffer);
    delay(1000);
  }
}
