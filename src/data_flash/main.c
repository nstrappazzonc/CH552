#include <ch552.h>
#include <utils.h>

#define RED    P34
#define GREEN  P33
#define BLUE   P11
#define BUTTON P32

uint8_t WriteDataFlash(uint8_t Addr,unsigned char *buf,uint8_t len) {
    uint8_t i;
    SAFE_MOD = 0x55;
    SAFE_MOD = 0xAA;
    GLOBAL_CFG |= bDATA_WE;
    SAFE_MOD = 0;
    ROM_ADDR_H = DATA_FLASH_ADDR >> 8;

    Addr <<= 1;
    for(i=0;i<len;i++) {
        ROM_ADDR_L = Addr + i*2;
        ROM_DATA_L = *(buf+i);
        if ( ROM_STATUS & bROM_ADDR_OK ) {
           ROM_CTRL = ROM_CMD_WRITE;
        }
        if((ROM_STATUS ^ bROM_ADDR_OK) > 0) return i;
      }
    SAFE_MOD = 0x55;
    SAFE_MOD = 0xAA;
    GLOBAL_CFG &= ~bDATA_WE;
    SAFE_MOD = 0;
    return i;
}

uint8_t ReadDataFlash(uint8_t Addr,uint8_t len,unsigned char *buf) {
    uint8_t i;
    ROM_ADDR_H = DATA_FLASH_ADDR >> 8;
    Addr <<= 1;
    for(i=0;i<len;i++) {
      ROM_ADDR_L = Addr + i*2;
      ROM_CTRL = ROM_CMD_READ;
      *(buf+i) = ROM_DATA_L;
    }
    return i;
}

void main(void) {
    init();

    uint8_t color;

    ReadDataFlash(1, 1, &color);
    switch(color) {
        case 1:
            RED = 1;
            break;
        case 2:
            GREEN = 1;
            break;
        case 3:
            BLUE = 1;
            break;
        default:
            break;
    }

    //Set input in pullup mode:
    P3_MOD_OC |= (1<<BUTTON);
    P3_DIR_PU |= (1<<BUTTON);

    while(1) {
        if(BUTTON) {
            delay(50);

            if(BUTTON) {
                color++;
                if (color > 3) {
                    color = 0;
                }

                WriteDataFlash(1, &color, 1);

                RED   = 0;
                GREEN = 0;
                BLUE  = 0;

                switch(color) {
                    case 1:
                        RED = 1;
                        break;
                    case 2:
                        GREEN = 1;
                        break;
                    case 3:
                        BLUE = 1;
                        break;
                    default:
                        break;
                }

                while(BUTTON);
            }
        }
    }
}
