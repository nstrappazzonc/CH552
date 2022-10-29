#include <stdint.h>
#include <ch552.h>

void init(void) {
    // Set internal oscilator:
    SAFE_MOD = 0x55;
    SAFE_MOD = 0xAA;
    CLOCK_CFG = CLOCK_CFG & ~ MASK_SYS_CK_SEL | 0x06; // 24MHz

    // Put off:
    P11 = 0;
    P14 = 0;
    P15 = 0;
    P16 = 0;
    P17 = 0;
    P30 = 0;
    P31 = 0;
    P32 = 0;
    P33 = 0;
    P34 = 0;
    P36 = 0;
    P37 = 0;
}

void delay_us(uint16_t n) {
    while(n) {
        ++SAFE_MOD;
        ++SAFE_MOD;
        --n;
    }
}

void delay(uint16_t n) {
    while(n) {
        delay_us(1000); 
        --n;
    }
}
