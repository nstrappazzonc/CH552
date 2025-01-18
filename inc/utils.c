#include <ch552.h>
#include <stdint.h>

// Delay in us (microseconds) There are 1000 microseconds in a milliseconds:
void delay_us(uint16_t n) {
  // n >>= 2;
	while (n) {
		++ SAFE_MOD;
    ++ SAFE_MOD;
    ++ SAFE_MOD;
    ++ SAFE_MOD;
    ++ SAFE_MOD;
    ++ SAFE_MOD;
    // ++ SAFE_MOD;
    -- n;
	}

  // __asm__(
  //     ".even                                    \n"
  //     "    mov  r6, dpl                         \n" // low 8-bit
  //     "    mov  r7, dph                         \n" // high 8-bit
  //     "    clr  c                               \n"
  //     "    mov  a,#0x01                         \n"
  //     "    subb a, r6                           \n"
  //     "    clr  a                               \n"
  //     "    subb a, r7                           \n"
  //     "    jc skip_0us$                         \n"
  //     "    ret                                  \n" // return if 0 1 us
  //                                                   // about 1.2us total
  //     "    nop                                  \n"
  //     "skip_0us$:                               \n"
  //     "    clr  c                               \n" // do some loop init, not
  //                                                   // useful for 2us but better
  //                                                   // here
  //     "    mov  a, #0x02                        \n"
  //     "    subb a, r6                           \n"
  //     "    mov  r6, a                           \n"
  //     "    mov  a, #0x00                        \n"
  //     "    subb a, r7                           \n"
  //     "    mov  r7, a                           \n"

  //     "    nop                                  \n" // keep even
  //     "    cjne r6,#0x00,loop24m_us$            \n"
  //     "    cjne r7,#0x00,loop24m_us$            \n"
  //     "    nop                                  \n"
  //     "    ret                                  \n" // return if 2us  about 2 us
  //                                                   // total

  //     "loop24m_us$:                             \n" // about nus

  //     "    nop \n nop \n nop \n nop \n nop \n    " // 6+11 cycle
  //     "    nop \n "
  //     "loop24m_us_2$:                          \n" // need more test

  //     "    nop \n nop \n nop \n nop \n nop \n    "
  //     "    nop \n nop \n nop \n nop \n nop \n    "
  //     "    nop \n                                "

  //     "    inc  r6                              \n" // 1 cycle
  //     "    cjne r6, #0,loop24m_us$              \n" // 6 cycle
  //     "    inc  r7                              \n" // there will be extra 1
  //                                                   // cycles for every 256us
  //     "    cjne r7, #0,loop24m_us_2$            \n"
  //     "    nop                                  \n");
}

// Delay in ms (milliseconds). There are 1000 milliseconds in a second:
void delay(uint16_t n) {
  while (n) {
    delay_us(1000);
    --n;
  }
}

void init(void) {
  // Set to low all pins P1.x and P3.x:
  P1 = 0;
  P3 = 0;

  // Set internal oscilator:
  SAFE_MOD = 0x55;
  SAFE_MOD = 0xAA;
  CLOCK_CFG = CLOCK_CFG & ~MASK_SYS_CK_SEL | 0x06; // 24MHz
  SAFE_MOD = 0x00;
  delay_us(5000); // Is needed to stablize internal RC.
}
