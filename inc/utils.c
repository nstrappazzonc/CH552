#include <ch552.h>

// Function for microsecond delay
void delay_us(unsigned int us) {
    unsigned char interrupt_state = EA; // Save the current interrupt state
    EA = 0; // Disable global interrupts to ensure precise timing

    unsigned int initial_value;

    // Limit the maximum delay to 65,535 μs
    if (us > 65535) {
        us = 65535;
    }

    // Calculate the initial timer value for the desired delay
    initial_value = 65536 - us;

    // Configure Timer 0 in Mode 1 (16-bit mode)
    TMOD = 0x01; 
    TH0 = (initial_value >> 8) & 0xFF; // Set the high byte
    TL0 = initial_value & 0xFF;       // Set the low byte

    // Start Timer 0
    TR0 = 1;
    // Wait for Timer 0 to overflow
    while (TF0 == 0);
    // Stop Timer 0 and clear the overflow flag
    TR0 = 0;
    TF0 = 0;

    // Restore the previous interrupt state
    EA = interrupt_state;
}

// Function for millisecond delay
void delay_ms(unsigned int ms) {
    unsigned char interrupt_state = EA; // Save the current interrupt state
    EA = 0; // Disable global interrupts to ensure precise timing

    // Loop through each millisecond, using delay_us(1000)
    while (ms > 0) {
        delay_us(1000); // 1 millisecond = 1000 microseconds
        ms--;
    }

    // Restore the previous interrupt state
    EA = interrupt_state;
}

void init(void) {
  // Set to low all pins P1.x and P3.x:
  P1 = 0;
  P3 = 0;

  // Set internal oscilator:
  SAFE_MOD = 0x55;
  SAFE_MOD = 0xAA;
  // CLOCK_CFG = CLOCK_CFG & ~ MASK_SYS_CK_SEL | 0x07;  // 32MHz	
	// CLOCK_CFG = CLOCK_CFG & ~ MASK_SYS_CK_SEL | 0x06;  // 24MHz	
  // CLOCK_CFG = CLOCK_CFG & ~ MASK_SYS_CK_SEL | 0x05;  // 16MHz	
  CLOCK_CFG = CLOCK_CFG & ~ MASK_SYS_CK_SEL | 0x04;  // 12MHz
  // CLOCK_CFG = CLOCK_CFG & ~ MASK_SYS_CK_SEL | 0x03;  // 6MHz	
  // CLOCK_CFG = CLOCK_CFG & ~ MASK_SYS_CK_SEL | 0x02;  // 3MHz	
  // CLOCK_CFG = CLOCK_CFG & ~ MASK_SYS_CK_SEL | 0x01;  // 750KHz	
  // CLOCK_CFG = CLOCK_CFG & ~ MASK_SYS_CK_SEL | 0x00;  // 187.5MHz
  SAFE_MOD = 0x00;
}
