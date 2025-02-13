/******************************************************************************
 * File Name          : ch552.h
 * Author             : Nicola Strappazzon C.
 * Version            : V1.0
 * Date               : 2023/12/27
 * Description        : Header file for CH552 microcontrollers.
 *******************************************************************************/

#ifndef __CH552_H__
#define __CH552_H__

#pragma once
#include <compiler.h>

// #define F_CPU 24000000 // Default clock frequency.

// Registers:
// ----------
SFR(ADC_CFG, 0x9A);   // ADC configuration register.
SFR(ADC_CTRL, 0x80);  // ADC control register.
SFR(ADC_DATA, 0x9F);  // ADC data register. Is ReadOnly.
SFR(CLOCK_CFG, 0xB9); // System clock configuration register.
SFR(IE, 0xA8);        // Interrupt enable register.
SFR(IE_EX, 0xE8);     // Extend interrupt enable register.
SFR(P1, 0x90);        // P1 port input & output.
SFR(P1_DIR_PU, 0x93); // P1 port direction control and pull up enable  register.
SFR(P1_MOD_OC, 0x92); // P1 port output mode register.
SFR(P3, 0xB0);        // P3 port input & output.
SFR(P3_DIR_PU, 0x97); // P3 port direction control and pull up enable  register.
SFR(P3_MOD_OC, 0x96); // P3 port output mode register.
SFR(PCON, 0x87);      // Power control register (in power on reset state).
SFR(PIN_FUNC, 0xC6);  // Pin function selection register.
SFR(PWM_CK_SE, 0x9E); // PWM clock setting register.
SFR(PWM_CTRL, 0x9D);  // PWM control register.
SFR(PWM_DATA1, 0x9C); // PWM1 data register.
SFR(PWM_DATA2, 0x9B); // PWM2 data register.
SFR(SAFE_MOD, 0xA1);  // Safe mode control register (write only).
SFR(SBUF, 0x99);      // UART0 data register.
SFR(SCON, 0x98);      // UART0 control register.
SFR(T2CON, 0xC8);     // Timer2 control register.
SFR(T2MOD, 0xC9);     // Timer2 mode register.
SFR(TCON, 0x88);      // Timer0/1 control register.
SFR(TH1, 0x8D);       // Timer1 count high bit.
SFR(TMOD, 0x89);      // Timer0/1 mode register.
SFR(TL0, 0x8A); // low byte of timer 0 count
SFR(TL1, 0x8B); // low byte of timer 1 count
SFR(TH0, 0x8C); // high byte of timer 0 count

SFR(UDEV_CTRL, 0xD1);  // USB device port control register.
SFR(UEP0_CTRL, 0xDC);  // Endpoint0 control register.
SFR(UEP0_T_LEN, 0xDD); // Endpoint0 transmission length register.
SFR(UEP1_CTRL, 0xD2);  // Endpoint1 control register.
SFR(UEP1_T_LEN, 0xD3); // Endpoint1 transmission length register.
SFR(UEP2_3_MOD, 0xEB); // Endpoint2, endpoint3 mode control register.
SFR(UEP2_CTRL, 0xD4);  // Endpoint2 control register.
SFR(UEP2_T_LEN, 0xD5); // Endpoint2 transmission length register.
SFR(UEP4_1_MOD, 0xEA); // Endpoint1, endpoint4 mode control register.
SFR(USB_CTRL, 0xE2);   // USB control register.
SFR(USB_DEV_AD, 0xE3); // USB device address register.
SFR(USB_INT_EN, 0xE1); // USB interrupt enable register.
// SFR(USB_INT_FG, 0xD8); // USB interrupt flag register.
SFR(USB_INT_ST, 0xD9); // USB interrupt status register (read only).
SFR(USB_RX_LEN, 0xDB); // USB reception length register (read only).
SFR16(UEP0_DMA, 0xEC); // UEP0_DMA_L and UEP0_DMA_H constitute a 16-bit SFR.
SFR16(UEP1_DMA, 0xEE); // UEP1_DMA_L and UEP1_DMA_H constitute a 16-bit SFR.
SFR16(UEP2_DMA, 0xE4); // UEP2_DMA_L and UEP2_DMA_H constitute a 16-bit SFR.

// System Registers:
// -----------------
SFR(PSW, 0xD0);          // program status word
SBIT(CY, 0xD0, 7);       // carry flag
SBIT(AC, 0xD0, 6);       // auxiliary carry flag
SBIT(F0, 0xD0, 5);       // bit addressable general purpose flag 0
SBIT(RS1, 0xD0, 4);      // register R0-R7 bank selection high bit
SBIT(RS0, 0xD0, 3);      // register R0-R7 bank selection low bit
#define MASK_PSW_RS 0x18 // bit mask of register R0-R7 bank selection
                         // RS1 & RS0: register R0-R7 bank selection
                         //    00 - bank 0, R0-R7 @ address 0x00-0x07
                         //    01 - bank 1, R0-R7 @ address 0x08-0x0F
                         //    10 - bank 2, R0-R7 @ address 0x10-0x17
                         //    11 - bank 3, R0-R7 @ address 0x18-0x1F
SBIT(OV, 0xD0, 2);       // overflow flag
SBIT(F1, 0xD0, 1);       // bit addressable general purpose flag 1
SBIT(P, 0xD0, 0);        // ReadOnly: parity flag
SFR(ACC, 0xE0);          // accumulator
SFR(B, 0xF0);            // general purpose register B
SFR(SP, 0x81);           // stack pointer
SFR(DPL, 0x82);          // data pointer low
SFR(DPH, 0x83);          // data pointer high
SFR(SAFE_MOD, 0xA1);     // WriteOnly: writing safe mode
#define CHIP_ID SAFE_MOD
SFR(GLOBAL_CFG, 0xB1); // global config, Write@SafeMode
#define bBOOT_LOAD                                                             \
  0x20 // ReadOnly: boot loader status for discriminating BootLoader or
       // Application: set 1 by power on reset, clear 0 by software reset
#define bSW_RESET 0x10 // software reset bit, auto clear by hardware
#define bCODE_WE                                                               \
  0x08 // enable flash-ROM (include code & Data-Flash) being program or erasing:
       // 0=writing protect, 1=enable program and erase
#define bDATA_WE                                                               \
  0x04 // enable Data-Flash (flash-ROM data area) being program or erasing:
       // 0=writing protect, 1=enable program and erase
#define bLDO3V3_OFF                                                            \
  0x02 // disable 5V->3.3V LDO: 0=enable LDO for USB and internal oscillator
       // under 5V power, 1=disable LDO, V33 pin input external 3.3V power
#define bWDOG_EN                                                               \
  0x01 // enable watch-dog reset if watch-dog timer overflow: 0=as timer only,
       // 1=enable reset if timer overflow

// Interrupt routine address and interrupt number:
// -----------------------------------------------
#define INT_NO_USB 8 // interrupt number for USB

// Power Control Register (PCON):
// ------------------------------
#define SMOD                                                                   \
  0x80 // When the UART0 baud rate is generated by timer 1, select the
       // communication baud rate of UART0 mode 1, 2 and 3:
       // - 0: Slow mode.
       // - 1: Fast mode.
#define bRST_FLAG1 0x20 // Last reset flag high bit 0.
#define bRST_FLAG0 0x10 // Last reset flag low bit 1.
#define GF1 0x08 // General flag bit 1. User-defined. Reset and set by software.
#define GF0 0x04 // General flag bit 0. User-defined. Reset and set by software.
#define PD                                                                     \
  0x02 // Sleep mode enable. Sleep after set to 1. Automatically reset by
       // hardware after wakeup.

// FlashROM and Data-Flash Registers:
// ----------------------------------
SFR(GLOBAL_CFG, 0xB1); // global config, Write@SafeMode:
#define bBOOT_LOAD                                                             \
  0x20 // ReadOnly: boot loader status for discriminating BootLoader or
       // Application: set 1 by power on reset, clear 0 by software reset.
#define bSW_RESET 0x10 // software reset bit, auto clear by hardware.
#define bCODE_WE                                                               \
  0x08 // enable flash-ROM (include code & Data-Flash) being program or erasing:
       // 0=writing protect, 1=enable program and erase.
#define bDATA_WE                                                               \
  0x04 // enable Data-Flash (flash-ROM data area) being program or erasing:
       // 0=writing protect, 1=enable program and erase.
#define bLDO3V3_OFF                                                            \
  0x02 // disable 5V->3.3V LDO: 0=enable LDO for USB and internal oscillator
       // under 5V power, 1=disable LDO, V33 pin input external 3.3V power.
#define bWDOG_EN                                                               \
  0x01 // enable watch-dog reset if watch-dog timer overflow: 0=as timer only,
       // 1=enable reset if timer overflow.

SFR16(ROM_ADDR, 0x84); // address for flash-ROM, little-endian
SFR(ROM_ADDR_L, 0x84); // address low byte for flash-ROM
SFR(ROM_ADDR_H, 0x85); // address high byte for flash-ROM
SFR16(ROM_DATA, 0x8E); // data for flash-ROM writing, little-endian
SFR(ROM_DATA_L, 0x8E); // data low byte for flash-ROM writing, data byte for
                       // Data-Flash reading/writing
SFR(ROM_DATA_H, 0x8F); // data high byte for flash-ROM writing
SFR(ROM_CTRL, 0x86);   // WriteOnly: flash-ROM control

#define DATA_FLASH_ADDR 0xC000 // start address of Data-Flash.
#define ROM_CMD_WRITE                                                          \
  0x9A // WriteOnly: flash-ROM word or Data-Flash byte write operation command
#define ROM_CMD_READ 0x8E // WriteOnly: Data-Flash byte read operation command
#define ROM_STATUS ROM_CTRL
#define bROM_ADDR_OK                                                           \
  0x40 // ReadOnly: flash-ROM writing operation address valid flag, can be
       // reviewed before or after operation: 0=invalid parameter, 1=address
       // valid
#define bROM_CMD_ERR                                                           \
  0x02 // ReadOnly: flash-ROM operation command error flag: 0=command accepted,
       // 1=unknown command

// Interrupt Registers:
// --------------------
SFR(GPIO_IE, 0xC7); // GPIO interrupt enable:
#define bIE_IO_EDGE                                                            \
  0x80 // enable GPIO edge interrupt: 0=low/high level, 1=falling/rising edge.
#define bIE_RXD1_LO 0x40 // enable interrupt by RXD1 low level / falling edge.
#define bIE_P1_5_LO                                                            \
  0x20 // enable interrupt by pin P1.5 low level / falling edge.
#define bIE_P1_4_LO                                                            \
  0x10 // enable interrupt by pin P1.4 low level / falling edge.
#define bIE_P1_3_LO                                                            \
  0x08 // enable interrupt by pin P1.3 low level / falling edge.
#define bIE_RST_HI 0x04 // enable interrupt by pin RST high level / rising edge.
#define bIE_P3_1_LO                                                            \
  0x02 // enable interrupt by pin P3.1 low level / falling edge.
#define bIE_RXD0_LO 0x01 // enable interrupt by RXD0 low level / falling edge.

// Interrupt Enable Register (IE):
// -------------------------------
SBIT(EA, 0xA8, 7); // Enable global interrupts: 0=disable, 1=enable if E_DIS=0.
SBIT(E_DIS, 0xA8,
     6); // Disable global interrupts, intend to inhibit interrupt during some
         // flash-ROM operation: 0=enable if EA=1, 1=disable.
SBIT(ET2, 0xA8, 5); // Enable timer2 interrupt.
SBIT(ES, 0xA8, 4);  // Enable UART0 interrupt.
SBIT(ET1, 0xA8, 3); // Enable timer1 interrupt.
SBIT(EX1, 0xA8, 2); // Enable external interrupt INT1.
SBIT(ET0, 0xA8, 1); // Enable timer0 interrupt.
SBIT(EX0, 0xA8, 0); // Enable external interrupt INT0.

// Extend Interrupt Enable Register (IE_EX):
// -----------------------------------------
SBIT(IE_WDOG, 0xE8, 7);  // Enable watch-dog timer interrupt.
SBIT(IE_GPIO, 0xE8, 6);  // Enable GPIO input interrupt.
SBIT(IE_PWMX, 0xE8, 5);  // Enable PWM1/2 interrupt.
SBIT(IE_UART1, 0xE8, 4); // Enable UART1 interrupt.
SBIT(IE_ADC, 0xE8, 3);   // Enable ADC interrupt.
SBIT(IE_USB, 0xE8, 2);   // Enable USB interrupt.
SBIT(IE_TKEY, 0xE8, 1);  // Enable touch-key timer interrupt.
SBIT(IE_SPI0, 0xE8, 0);  // Enable SPI0 interrupt.

// System clock configuration register (CLOCK_CFG), only can be written in safe
// mode:
// ----------------------------------------------------------------------------------
#define bOSC_EN_INT                                                            \
  0x80 // Internal clock oscillator enable:
       // - 1: Internal clock oscillator enabled, and select the internal clock.
       // - 0: Internal clock oscillator disabled, and select the external
       // crystal oscillator to provide the clock.
#define bOSC_EN_XT                                                             \
  0x40 // External crystal oscillator enable:
       // - 1: P1.2/P1.3 pin used as XI/XO and the oscillator enabled. A quartz
       // crystal or ceramic oscillator needs to be externally connected between
       // the XI and XO.
       // - 0: External oscillator disabled.
#define bWDOG_IF_TO                                                            \
  0x20 // Watch dog timer interrupt flag
       // - 1: Interrupt triggered by the timer overflow signal.
       // - 0: No interrupt.
       // The bit is automatically reset when the watchdog count register
       // (WDOG_COUNT) is reloaded or after entering the corresponding interrupt
       // service program.
#define bROM_CLK_FAST                                                          \
  0x10            // flash-ROM reference clock frequency selection:
                  // - 0: Normal (if Fosc>=16MHz).
                  // - 1: Speed up (if Fosc<16MHz).
#define bRST 0x08 // RST pin state input bit.
#define MASK_SYS_CK_SEL                                                        \
  0x07 // System clock selection [2:0], by default is set to 24MHz.
// -------------------------------------------------------------------------------
//                 |   System clock   | Relation with crystal | Fsys when |
// MASK_SYS_CK_SEL | frequency (Fsys) |    frequency (Fxt)    | Fosc=24MHz | [2]
// [1] [0]     |                  |                       |                  |
// ================|==================|=======================|==================|
//  0   0   0      |Fpll / 512        |Fxt / 128              |187.5KHz | 0   0
//  1      |Fpll / 128        |Fxt / 32               |750KHz            | 0   1
//  0      |Fpll / 32         |Fxt / 8                |3MHz              | 0   1
//  1      |Fpll / 16         |Fxt / 4                |6MHz              | 1   0
//  0      |Fpll / 8          |Fxt / 2                |12MHz             | 1   0
//  1      |Fpll / 6          |Fxt / 1.5              |16MHz             | 1   1
//  0      |Fpll / 4          |Fxt / 1                |24MHz (Default)   | 1   1
//  1      |Fpll / 3          |Fxt / 0.75             |Reserved, disabled|
// -------------------------------------------------------------------------------
//

// ADC Configuration Register (ADC_CFG):
// -------------------------------------
#define bADC_EN                                                                \
  0x08 // Power enable bit of ADC module:
       // - 0: ADC module power off, and enter the sleep state.
       // - 1: ADC module power ON.
#define bCMP_EN                                                                \
  0x04 // Power control bit of voltage comparator:
       // - 0: Voltage comparator power OFF. Enter the sleep state.
       // - 1: ON.
#define bADC_CLK                                                               \
  0x01 // ADC reference clock frequency selection bit, if the bit is 0, select
       // the slow clock, and 384 Fosc cycles are required for each ADC. If the
       // bit is 1, select the fast clock, and 96 Fosc cycles are required for
       // each ADC.

// ADC Control Register (ADC_CTRL):
// --------------------------------
SBIT(CMPO, 0x80, 7);   // Result output bit of the voltage comparator:
                       // - 0: Voltage of the positive phase input is lower than
                       // that of the inverted input terminal.
                       // - 1: Voltage of the positive phase input terminal is
                       // higher than that of the inverted input terminal.
SBIT(CMP_IF, 0x80, 6); // Voltage comparator result change flag:
                       // - 1: Voltage comparator results have changed. Directly
                       // write 0 to reset.
SBIT(ADC_IF, 0x80,
     5); // ADC conversion completed interrupt flag:
         // - 1: One ADC conversion is completed. Directly write 0 to reset.
SBIT(ADC_START, 0x80,
     4); // ADC start control bit. Set 1 to start an ADC conversion. This bit is
         // reset automatically after the ADC conversion is completed.
SBIT(CMP_CHAN, 0x80,
     3); // Voltage comparator inverted input terminal selection:
         // - 0: AIN1
         // - 1: AIN3
SBIT(ADC_CHAN1, 0x80, 1); // Voltage comparator positive phase input and ADC
                          // input channel selection high bit.
SBIT(ADC_CHAN0, 0x80, 0); // Voltage comparator positive phase input and ADC
                          // input channel selection low bit.

// UART0 Control Register (SCON):
// ------------------------------
SBIT(SM0, 0x98, 7); // UART0 working mode selection bit 0:
                    // - 0: 8-bit data asynchronous communication.
                    // - 1: 9-bit data asynchronous communication.
SBIT(SM1, 0x98,
     6); // UART0 working mode selection bit 1:
         // - 0: Fixed baud rate.
         // - 1: Variable baud rate, which is generated by timer T1 or T2.
SBIT(SM2, 0x98,
     5); // UART0 multi-device communication control bit:
         // In mode 2 and mode 3,
         //   When SM2=1,
         //     If RB8 is 0, RI is not set to 1 and the reception is invalid.
         //     If RB8 is 1, RI is set to 1 and the reception is valid.
         //   When SM2=0, no matter RB8 is 0 or 1, RI is set when receiving data
         //   and the reception is valid.
         // In mode 1, if SM2=1, only when the active stop bit is received can
         // the reception be valid; In mode 0, the SM2 bit must be set to 0.
SBIT(REN, 0x98, 4); // UART0 receive enable bit:
                    // - 0: Receive disabled.
                    // - 1: Receive enabled.
SBIT(TB8, 0x98, 3); // The 9th bit of the transmitted data:
                    // In modes 2 and mode 3, TB8 is used to write the 9th bit
                    // of the transmitted data, which can be a parity bit. In
                    // multi-device communication, it is used to indicate
                    // whether the host sends an address byte or a data byte.
                    // Data byte when TB8=0, and address byte when TB8=1.
SBIT(RB8, 0x98, 2); // The 9th bit of the received data:
                    // In mode 2 and 3, RB8 is used to store the 9th bit of the
                    // received data. In mode 1, if SM2=0, RB8 is used to store
                    // the received stop bit. In mode 0, RB8 is not used.
SBIT(TI, 0x98, 1); // Transmit interrupt flag bit. Set by hardware at the end of
                   // a data byte transmission. It requires software to reset.
SBIT(RI, 0x98, 0); // Receive interrupt flag bit. Set by hardware at the end of
                   // a data byte reception. It requires software to reset.

// Timer/Counter 0/1 Mode Register (TMOD):
// ---------------------------------------
#define bT1_GATE                                                               \
  0x80 // Gate control enable bit. This bit controls whether the Timer1 startup
       // is affected by INT1:
       // - 0: Whether the timer/counter 1 is started is independent of INT1.
       // - 1: It is started only when the INT1 pin is at high level and TR1
       // is 1.
#define bT1_CT                                                                 \
  0x40 // Timing/counting mode selection bit:
       // - 0: It works in timing mode.
       // - 1: It works in counting mode. Falling edge on T1 pin selected as the
       // clock.
#define bT1_M1 0x20 // Timer/counter 1 mode selection high bit.
#define bT1_M0 0x30 // Timer/counter 1 mode selection low bit.
#define bT0_GATE                                                               \
  0x08 // Gate control enable bit. This bit controls whether the Timer0 startup
       // is affected by INT0.
       // - 0: Whether the timer/counter 0 is started is independent of INT0.
       // - 1: It is started only when the INT0 pin is at high level and TR0
       // is 1.
#define bT0_CT                                                                 \
  0x04 // Timing/counting mode selection bit:
       // - 0: It works in timing mode.
       // - 1: It works in counting mode. Falling edge on T0 pin selectd as the
       // clock.
#define bT0_M1 0x02 // Timer/counter 0 mode selection high bit.
#define bT0_M0 0x01 // Timer/counter 0 mode selection low bit.

// Timer/Counter 0/1 Control Register (TCON):
// ------------------------------------------
SBIT(TF1, 0x88, 7); // Timer1 overflow interrupt flag bit. Automatically cleared
                    // after it enters Timer1 interrupt.
SBIT(TR1, 0x88, 6); // Timer1 startup/stop bit. Set to 1 to startup. Set and
                    // cleared by software.
SBIT(TF0, 0x88, 5); // Timer0 overflow interrupt flag bit. Automatically cleared
                    // after it enters Timer0 interrupt.
SBIT(TR0, 0x88, 4); // Timer0 startup/stop bit. Set to 1 to startup. Set and
                    // cleared by software.
SBIT(IE1, 0x88, 3); // INT1 interrupt request flag bit. Automatically cleared
                    // after entering INT1 interrupt.
SBIT(IT1, 0x88, 2); // INT1 trigger mode control bit:
                    // - 0: INT1 triggered by low level.
                    // - 1: INT1 triggered by falling edge.
SBIT(IE0, 0x88, 1); // INT0 interrupt request flag bit. Automatically cleared
                    // after it enters INT0 interrupt.
SBIT(IT0, 0x88, 0); // INT0 trigger mode control bit:
                    // 0: INT0 triggered by low level.
                    // 1: INT0 triggered by falling edge.

// Bit masks for timer1 mode:
#define MASK_T1_MOD 0x30 // Bit mask of timer1 mode
#define MASK_T0_MOD 0x03 // Bit mask of timer0 mode

// Timer/counter 2 control register (T2CON):
// -----------------------------------------
SBIT(TF2, 0xC8, 7); // Timer2 overflow interrupt flag when bT2_CAP1_EN=0 When
                    // the Timer2 counts of all 16 bits change from 1 to 0, this
                    // overflow flag is set to 1, which requires software to
                    // reset. When RCLK=1 or TCLK=1, the bit is not set to 1.
SBIT(CAP1F, 0xC8,
     7); // Timer2 capture 1 interrupt flag when bT2_CAP1_EN=1. It is triggered
         // by the active edge on T2, which requires software to reset.
SBIT(EXF2, 0xC8,
     6); // Timer2 external trigger flag. It is triggered by T2EX active edge
         // and set to 1 when EXEN2=1, which requires software to reset.
SBIT(RCLK, 0xC8,
     5); // UART0 receive clock selection:
         // - 0: Timer1 overflow pulse selected to generate baud rate.
         // - 1: Timer2 overflow pulse selected to generate the baud rate.
SBIT(TCLK, 0xC8,
     4); // UART0 transmit clock selection:
         // - 0: Timer1 overflow pulse selected to generate baud rate.
         // - 1: Timer2 overflow pulse selected to generate the baud rate.
SBIT(EXEN2, 0xC8,
     3); // T2EX trigger enable bit:
         // - 0: Ignore T2EX.
         // - 1: Reload or capture enabled to be triggered by T2EX active edge.
SBIT(TR2, 0xC8, 2); // Timer2 startup/stop bit 0. Set to 1 to start. Set and
                    // cleared by software.
SBIT(C_T2, 0xC8,
     1); // Timer2 clock source selection bit:
         // - 0: Internal clock selected.
         // - 1: Edge count based on falling edge on T2 pin selected.
SBIT(CP_RL2, 0xC8, 0); // Timer2 function selection bit. This bit should be
                       // forced to be 0 if RCLK or TCLK is 1:
                       // - 0: Timer2 selected as timer/counter to automatically
                       // reload the initial value of the count when the counter
                       // overflows or T2EX level changes.
                       // - 1: Timer2 capture 2 function enabled. The active
                       // edge on T2EX is captured.

// Timer/counter 2 mode register (T2MOD):
// --------------------------------------
#define bTMR_CLK                                                               \
  0x80 // Fastest clock mode enable of T0/T1/T2 timer which has selected fast
       // clock:
       // - 1: Fsys without division as the count clock.
       // - 0: Divided clock selected.
       // This bit has no effect on the timer that selects the standard clock.
#define bT2_CLK                                                                \
  0x40 // Timer2 internal clock frequency selection bit:
       // - 0: Standard clock selected. Fsys/12 when in timing/counting mode.
       // Fsys/4 when in UART0 clock mode.
       // - 1: Fast clock selected. Fsys/4 (bTMR_CLK=0) or Fsys (bTMR_CLK=1)
       // when in timing/counting mode. Fsys/2 (bTMR_CLK=0) or Fsys (bTMR_CLK=1)
       // when in UART0 clock mode.
#define bT1_CLK                                                                \
  0x20 // Timer1 internal clock frequency selection bit:
       // - 0: Standard clock selected, Fsys/12.
       // - 1: Fast clock selected. Fsys/4 (bTMR_CLK=0) or Fsys (bTMR_CLK=1).
#define bT0_CLK                                                                \
  0x10 // Timer0 internal clock frequency selection bit:
       // - 0: Standard clock selected, Fsys/12.
       // - 1: Fast clock selected, Fsys/4 (bTMR_CLK=0) or Fsys (bTMR_CLK=1).
#define bT2_CAP_M1 0x08 // Timer2 capture mode high bit.
#define bT2_CAP_M0 0x04 // Timer2 capture mode low bit.
#define T2OE                                                                   \
  0x02 // Timer2 clock output enable bit:
       // - 0: Output disabled.
       // - 1: T2 pin enabled to output clock. The frequency is the half of the
       // Timer2 overflow rate.
#define bT2_CAP1_EN                                                            \
  0x01 // Capture 1 mode enable when RCLK=0, TCLK=0, CP_RL2=1, C_T2=0 and
       // T2OE=0:
       // - 1: Capture 1 function enabled. Active edge on T2 is captured.
       // - 0: Capture 1 function disabled.

// Pin Function Selection Register (PIN_FUNC):
// -------------------------------------------
#define bUSB_IO_EN                                                             \
  0x80 // USB UDP/UDM pin enable bit:
       // - 0: P3.6/P3.7 selected for GPIO. P3_DIR_PU can be used to control
       // pull-up resistor, and P3_MOD_OC is supported.
       // - 1: P3.6/P3.7 selected for UDP/UDM, controlled by USB module, and
       // P3_DIR_PU and P3_MOD_OC both have no effect on it.
#define bIO_INT_ACT                                                            \
  0x40 // GPIO interrupt request activation status: When bIE_IO_EDGE=0:
       // - 1: GPIO inputs valid level and interrupts the request.
       // - 0: Input level is invalid. When bIE_IO_EDGE=1, the bit is used as
       // the edge interrupt flag, 1: Valid edge is detected and the bit cannot
       // be reset by software and can only be reset automatically in reset or
       // level interrupt mode or when entering the corresponding interrupt
       // service program.
#define bUART1_PIN_X                                                           \
  0x20 // UART1 pin mapping enable bit:
       // - 0: RXD1/TXD1 selects P1.6/P1.7.
       // - 1: RXD1/TXD1 selects P3.4/P3.2
#define bUART0_PIN_X                                                           \
  0x10 // UART1 pin mapping enable bit:
       // - 0: RXD1/TXD1 selects P1.6/P1.7.
       // - 1: RXD1/TXD1 selects P3.4/P3.2
#define bPWM2_PIN_X                                                            \
  0x08 // PWM2 pin mapping enable bit:
       // - 0: PWM2 selects P3.4.
       // - 1: PWM2 selects P3.1
#define bPWM1_PIN_X                                                            \
  0x04 // PWM1 pin mapping enable bit:
       // - 0: PWM1 selects P1.5.
       // - 1: PWM1 selects P3.0
#define bT2EX_PIN_X                                                            \
  0x02 // T2EX/CAP2 pin mapping enable bit:
       // - 0: T2EX/CAP2 selects P1.1.
       // - 1: T2EX/CAP2 selects RST
#define bT2_PIN_X                                                              \
  0x01 // T2/CAP1 pin mapping enable bit:
       // - 0: T2/CAP1 selects P1.0.
       // - 1: T2/CAP1 selects P1.4

// Port number 1:
// --------------
// SBIT(P10, 0x90, 0); // P1.0
// SBIT(P11, 0x90, 1); // P1.1
// SBIT(P12, 0x90, 2); // P1.2
// SBIT(P13, 0x90, 3); // P1.3
// SBIT(P14, 0x90, 4); // P1.4
// SBIT(P15, 0x90, 5); // P1.5
// SBIT(P16, 0x90, 6); // P1.6
// SBIT(P17, 0x90, 7); // P1.7

// Port number 3:
// --------------
// SBIT(P30, 0xB0, 0); // P3.0
// SBIT(P31, 0xB0, 1); // P3.1
// SBIT(P32, 0xB0, 2); // P3.2
// SBIT(P33, 0xB0, 3); // P3.3
// SBIT(P34, 0xB0, 4); // P3.4
// SBIT(P35, 0xB0, 5); // P3.5
// SBIT(P36, 0xB0, 6); // P3.6
// SBIT(P37, 0xB0, 7); // P3.7

// Port alias:
// -----------
#define bAIN0 0x02 // P1.1: AIN0 for ADC
#define bAIN1 0x10 // P1.4: AIN1 for ADC
#define bAIN2 0x20 // P1.5: AIN2 for ADC
#define bAIN3 0x04 // P3.3: AIN3 for ADC

// PWM control register (PWM_CTRL):
// --------------------------------
SBIT(bPWM_IE_END, 0x9D, 7); // PWM cycle end or MFM buffer interrupt enabled.
SBIT(bPWM2_POLAR, 0x9D, 6); // PWM2 output polarity control bit:
                            // - 0: Low level by default while active high.
                            // - 1: High level by default while active low.
SBIT(bPWM1_POLAR, 0x9D, 5); // PWM1 output polarity control bit:
                            // - 0: Low level by default while active high.
                            // - 1: High level by default while active low.
SBIT(bPWM_IF_END, 0x9D,
     4); // PWM cycle period end interrupt flag bit:
         // - 1: A PWM cycle period end interrupt. Write 1 to reset, or reset
         // when the PWM_DATA1 data is reloaded.
SBIT(bPWM2_OUT_EN, 0x9D, 3); // PWM2 output enable:
                             // - 1: PWM2 output enabled
SBIT(bPWM1_OUT_EN, 0x9D, 2); // PWM1 output enable:
                             // - 1: PWM1 output enabled
SBIT(bPWM_CLR_ALL, 0x9D, 1); // Empty PWM1 and PWM2 counts and FIFO.

// USB control register (USB_CTRL):
// --------------------------------
// #define bUC_LOW_SPEED 0x40 // USB bus signal transfer rate selection bit:
//                            // - 0: Full speed, 12Mbps.
//                            // - 1: Low speed, 1.5Mbps.
// #define bUC_DEV_PU_EN 0x20 // USB device enable and internal pull-up resistor
// control bit:
//                            // - 1: USB device transfer enabled and the
//                            internal pull-up resistor enabled.
// #define bUC_SYS_CTRL1 0x20 // USB system control high bit.
// #define bUC_SYS_CTRL0 0x10 // USB system control low bit.
// #define bUC_INT_BUSY  0x08 // Auto pause enable bit before the USB transfer
// completed interrupt flag is not reset:
//                            // - 1: It automatically pauses and responds to
//                            busy NAK before the UIF_TRANSFER interrupt flag is
//                            reset.
//                            // - 0: Not pause.
// #define bUC_RESET_SIE 0x04 // USB protocol processor software reset control
// bit:
//                            // - 1: Forcefully reset the USB protocol
//                            processor and most of the USB control registers,
//                            requires software to reset.
// #define bUC_CLR_ALL   0x02 // 1: Empty USB interrupt flag and FIFO, requires
// software to reset. #define bUC_DMA_EN    0x01 // 1: USB DMA and DMA interrupt
// enabled. 0: Disabled. #define MASK_UC_SYS_CTRL 0x30 // bit mask of USB system
// control bUC_HOST_MODE & bUC_SYS_CTRL1 & bUC_SYS_CTRL0: USB system control
//   0 00: disable USB device and disable internal pullup resistance
//   0 01: enable USB device and disable internal pullup resistance, need
//   external pullup resistance 0 1x: enable USB device and enable internal
//   pullup resistance 1 00: enable USB host and normal status 1 01: enable USB
//   host and force UDP/UDM output SE0 state 1 10: enable USB host and force
//   UDP/UDM output J state 1 11: enable USB host and force UDP/UDM output
//   resume or K state

// USB endpoint1, endpoint4 mode control register (UEP4_1_MOD):
#define bUEP1_RX_EN 0x80   // enable USB endpoint 1 receiving (OUT)
#define bUEP1_TX_EN 0x40   // enable USB endpoint 1 transmittal (IN)
#define bUEP1_BUF_MOD 0x10 // buffer mode of USB endpoint 1
#define bUEP4_RX_EN 0x08   // enable USB endpoint 4 receiving (OUT)
#define bUEP4_TX_EN 0x04   // enable USB endpoint 4 transmittal (IN)

#define bUC_DEV_PU_EN                                                          \
  0x20 // USB device enable and internal pullup resistance enable
#define bUC_DMA_EN 0x01 // DMA enable and DMA interrupt enable for USB
#define bUC_INT_BUSY                                                           \
  0x08 // enable automatic responding busy for device mode or automatic pause
       // for host mode during interrupt flag UIF_TRANSFER valid
#define bUD_PD_DIS                                                             \
  0x80 // disable USB UDP/UDM pulldown resistance: 0=enable pulldown, 1=disable
#define bUD_PORT_EN 0x01   // enable USB physical port I/O: 0=disable, 1=enable
#define bUEP2_BUF_MOD 0x01 // buffer mode of USB endpoint 2
#define bUEP2_RX_EN 0x08   // enable USB endpoint 2 receiving (OUT)
#define bUEP2_TX_EN 0x04   // enable USB endpoint 2 transmittal (IN)
#define bUEP_AUTO_TOG                                                          \
  0x10 // enable automatic toggle after successful transfer completion on
       // endpoint 1/2/3: 0=manual toggle, 1=automatic toggle
#define bUIE_BUS_RST                                                           \
  0x01 // enable interrupt for USB bus reset event for USB device mode
#define bUIE_SUSPEND 0x04  // enable interrupt for USB suspend or resume event
#define bUIE_TRANSFER 0x02 // enable interrupt for USB transfer completion
#define MASK_UIS_ENDP                                                          \
  0x0F // ReadOnly: bit mask of current transfer endpoint number for USB device
       // mode
#define MASK_UIS_TOKEN                                                         \
  0x30 // ReadOnly: bit mask of current token PID code received for USB device
       // mode
#define UEP_R_RES_ACK 0x00   //
#define UEP_T_RES_NAK 0x02   //
#define UEP_T_RES_NAK 0x02   //
#define UIS_TOKEN_SETUP 0x30 //
#define bUEP_R_TOG                                                             \
  0x80 // expected data toggle flag of USB endpoint X receiving (OUT): 0=DATA0,
       // 1=DATA1
#define bUEP_T_TOG                                                             \
  0x40 // prepared data toggle flag of USB endpoint X transmittal (IN): 0=DATA0,
       // 1=DATA1
#define UEP_R_RES_STALL 0x0C
#define UEP_T_RES_STALL 0x03
#define bUD_GP_BIT 0x02 // general purpose bit
#define MASK_UEP_T_RES                                                         \
  0x03 // bit mask of handshake response type for USB endpoint X transmittal
       // (IN)
#define UEP_T_RES_ACK 0x00
#define MASK_UEP_R_RES                                                         \
  0x0C // bit mask of handshake response type for USB endpoint X receiving (OUT)
#define UEP_R_RES_NAK 0x08
#define bUDA_GP_BIT 0x80 // general purpose bit
#define UIS_TOKEN_OUT 0x00
#define UIS_TOKEN_SOF 0x10
#define UIS_TOKEN_IN 0x20
#define UIS_TOKEN_SETUP 0x30
#define MASK_USB_ADDR 0x7F
SFR(USB_INT_FG, 0xD8); // USB interrupt flag
SBIT(U_IS_NAK, 0xD8,
     7); // ReadOnly: indicate current USB transfer is NAK received
SBIT(U_TOG_OK, 0xD8, 6); // ReadOnly: indicate current USB transfer toggle is OK
SBIT(U_SIE_FREE, 0xD8, 5);   // ReadOnly: indicate USB SIE free status
SBIT(UIF_FIFO_OV, 0xD8, 4);  // FIFO overflow interrupt flag for USB, direct bit
                             // address clear or write 1 to clear
SBIT(UIF_HST_SOF, 0xD8, 3);  // host SOF timer interrupt flag for USB host,
                             // direct bit address clear or write 1 to clear
SBIT(UIF_SUSPEND, 0xD8, 2);  // USB suspend or resume event interrupt flag,
                             // direct bit address clear or write 1 to clear
SBIT(UIF_TRANSFER, 0xD8, 1); // USB transfer completion interrupt flag, direct
                             // bit address clear or write 1 to clear
SBIT(UIF_DETECT, 0xD8, 0); // device detected event interrupt flag for USB host
                           // mode, direct bit address clear or write 1 to clear
SBIT(UIF_BUS_RST, 0xD8,
     0); // bus reset event interrupt flag for USB device mode, direct bit
         // address clear or write 1 to clear

SFR(USB_MIS_ST, 0xDA);    // ReadOnly: USB miscellaneous status
#define bUMS_SUSPEND 0x04 // ReadOnly: indicate USB suspend status
#define bUD_LOW_SPEED                                                          \
  0x04 // enable USB physical port low speed: 0=full speed, 1=low speed
#define bUC_LOW_SPEED 0x40 // enable USB low speed: 0=full speed, 1=low speed
SFR(XBUS_AUX, 0xA2);       // xBUS auxiliary setting

SBIT(U_TOG_OK, 0xD8, 6); // ReadOnly: indicate current USB transfer toggle is OK
SBIT(UIF_TRANSFER, 0xD8, 1); // USB transfer completion interrupt flag, direct
                             // bit address clear or write 1 to clear
#define bUC_RESET_SIE 0x04   // force reset USB SIE, need software clear
#define bUC_CLR_ALL 0x02     // force clear FIFO and count of USB
#endif
