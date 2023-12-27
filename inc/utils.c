#include <stdint.h>
#include <ch552.h>

void init(void) {
    // Set internal oscilator:
    SAFE_MOD = 0x55;
    SAFE_MOD = 0xAA;
    CLOCK_CFG = CLOCK_CFG & ~ MASK_SYS_CK_SEL | 0x06; // 24MHz
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
