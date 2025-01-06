#include <ch552.h>
#include <stdint.h>

void init(void) {
  // Set to low all pins P1.x and P3.x:
  P1 = 0;
  P3 = 0;

  // Set internal oscilator:
  SAFE_MOD = 0x55;
  SAFE_MOD = 0xAA;
  CLOCK_CFG = CLOCK_CFG & ~MASK_SYS_CK_SEL | 0x06; // 24MHz
}

// Delay in us (microseconds) There are 1000 microseconds in a milliseconds:
void delay_us(uint16_t n) {
  while (n) {
    ++SAFE_MOD;
    ++SAFE_MOD;
    --n;
  }
}

// Delay in ms (milliseconds). There are 1000 milliseconds in a second:
void delay(uint16_t n) {
  while (n) {
    delay_us(1000);
    --n;
  }
}
