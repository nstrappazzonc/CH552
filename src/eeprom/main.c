#include "stdio.h"
#include <ch552.h>
#include <eeprom.h>
#include <string.h>
#include <utils.h>

void main(void) {
    init();

    uint8_t i, m, len;
    uint16_t j = 0;

    while(1) {
        for(int i=0; i<128; i++){
            len = WriteDataFlash(i, &i, 1);
            if(len != 1){
                // printf("Write Err = %02x,m = %02x\n", j, (uint8_t)m);
            }
        }

        for(i=0;i<128;i++){
            len = ReadDataFlash(i,1,&m);
            if((len != 1) ||(m != i)){
                // printf("Read Err = %02x, = %02x,addr =%02x ,值= %02x\n",j,(uint8_t)(i*2),(uint8_t)ROM_DATA_L,(uint8_t)m);               
            }
        }
        // printf("$$OK %02x \n",j);
        j++;

        delay(1000);
    }
}

// hacer algo con un led y un pulsador para guardar el estado de la ultima vez que se presiono el boton, conectas y desconecta y carga el ultimo estado.
