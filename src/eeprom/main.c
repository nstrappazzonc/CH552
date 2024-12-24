#include "stdio.h"
#include <ch552.h>
#include <eeprom.h>
#include <string.h>
#include <utils.h>

void main(void) {
    uint8_t i,m,len;

    init();

    while(1) {
        for(int i=0;i<128;i++){
            len = WriteDataFlash(i,&i,1);

            delay(1000);
        }
    }
}
