#include <compiler.h>

/*  System Registers  */
SFR(SAFE_MOD,  0xA1); // WriteOnly: writing safe mode

/* Clock and Sleep and Power Registers */
SFR(CLOCK_CFG, 0xB9);        // System clock config: lower 3 bits for system clock Fsys, Write@SafeMode
#define MASK_SYS_CK_SEL 0x07 // Bit mask of system clock Fsys selection

/*  Port Registers  */
#define P1 0x90 // Port 1 input & output
#define P3 0xB0 // Port 3 input & output

SBIT(P11, P1, 0x01); // Port 1.1
SBIT(P14, P1, 0x04); // Port 1.4
SBIT(P15, P1, 0x05); // Port 1.5
SBIT(P16, P1, 0x06); // Port 1.6
SBIT(P17, P1, 0x07); // Port 1.7
SBIT(P30, P3, 0x00); // Port 3.0
SBIT(P31, P3, 0x01); // Port 3.1
SBIT(P32, P3, 0x02); // Port 3.2
SBIT(P33, P3, 0x03); // Port 3.3
SBIT(P34, P3, 0x04); // Port 3.4
SBIT(P36, P3, 0x06); // Port 3.6
SBIT(P37, P3, 0x07); // Port 3.7

#define bPWM2_PIN_X 0x08 // PWM2 alternate pin enable: 0=PWM2 on P3.4, 1=PWM2 on P3.1
#define bPWM1_PIN_X 0x04 // PWM1 alternate pin enable: 0=PWM1 on P1.5, 1=PWM1 on P3.0

// Pn_MOD_OC & Pn_DIR_PU: pin input & output configuration for Pn (n=1/3)
//   0 0:  float input only, without pullup resistance
//   0 1:  push-pull output, strong driving high level and low level
//   1 0:  open-drain output and input without pullup resistance
//   1 1:  quasi-bidirectional (standard 8051 mode), open-drain output and input with pullup resistance, just driving high level strongly for 2 clocks if turning output level from low to high
SFR(P1_MOD_OC, 0x92); // Port 1 output mode: 0=push-pull, 1=open-drain
SFR(P1_DIR_PU, 0x93); // Port 1 direction for push-pull or pullup enable for open-drain
SFR(P3_MOD_OC, 0x96); // Port 3 output mode: 0=push-pull, 1=open-drain
SFR(P3_DIR_PU, 0x97); // Port 3 direction for push-pull or pullup enable for open-drain

SFR(PIN_FUNC,  0xC6); // Pin function selection

/*  PWM1/2 Registers  */
#define bPWM_IE_END  0x80 // Enable interrupt for PWM mode cycle end
#define bPWM2_POLAR  0x40 // PWM2 output polarity: 0=default low and high action, 1=default high and low action
#define bPWM1_POLAR  0x20 // PWM1 output polarity: 0=default low and high action, 1=default high and low action
#define bPWM_IF_END  0x10 // Interrupt flag for cycle end, write 1 to clear or write PWM_CYCLE or load new data to clear
#define bPWM2_OUT_EN 0x08 // PWM2 output enable
#define bPWM1_OUT_EN 0x04 // PWM1 output enable
#define bPWM_CLR_ALL 0x02 // Force clear FIFO and count of PWM1/2

SFR(PWM_DATA2, 0x9B); // PWM data for PWM2
SFR(PWM_DATA1, 0x9C); // PWM data for PWM1
SFR(PWM_CTRL,  0x9D); // PWM 1/2 control
SFR(PWM_CK_SE, 0x9E); // Clock divisor setting
