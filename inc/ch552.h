#ifndef __CH552_H__
#define __CH552_H__

#include <compiler.h>
#include <lint.h>

// System SFRs
SFR(PSW, 0xD0);
SBIT(CY, 0xD0, 7);
SBIT(AC, 0xD0, 6);
SBIT(F0, 0xD0, 5);
SBIT(RS1, 0xD0, 4);
SBIT(RS0, 0xD0, 3);
SBIT(OV, 0xD0, 2);
SBIT(F1, 0xD0, 1);
SBIT(P, 0xD0, 0);
SFR(ACC, 0xE0);
SFR(B, 0xF0);
SFR(SP, 0x81);
SFR(DPL, 0x82);
SFR(DPH, 0x83);
SFR(SAFE_MOD, 0xA1);
SFR(GLOBAL_CFG, 0xB1);
SFR(PCON, 0x87);
SFR(CLOCK_CFG, 0xB9);
SFR(WAKE_CTRL, 0xA9);
SFR(RESET_KEEP, 0xFE);
SFR(WDOG_COUNT, 0xFF);

// Interrupt SFRs
SFR(IE, 0xA8);
SBIT(EA, 0xA8, 7);
SBIT(E_DIS, 0xA8, 6);
SBIT(ET2, 0xA8, 5);
SBIT(ES, 0xA8, 4);
SBIT(ET1, 0xA8, 3);
SBIT(EX1, 0xA8, 2);
SBIT(ET0, 0xA8, 1);
SBIT(EX0, 0xA8, 0);
SFR(IP, 0xB8);
SBIT(PH_FLAG, 0xB8, 7);
SBIT(PL_FLAG, 0xB8, 6);
SBIT(PT2, 0xB8, 5);
SBIT(PS, 0xB8, 4);
SBIT(PT1, 0xB8, 3);
SBIT(PX1, 0xB8, 2);
SBIT(PT0, 0xB8, 1);
SBIT(PX0, 0xB8, 0);
SFR(IE_EX, 0xE8);
SBIT(IE_WDOG, 0xE8, 7);
SBIT(IE_GPIO, 0xE8, 6);
SBIT(IE_PWMX, 0xE8, 5);
SBIT(IE_UART1, 0xE8, 4);
SBIT(IE_ADC, 0xE8, 3);
SBIT(IE_USB, 0xE8, 2);
SBIT(IE_TKEY, 0xE8, 1);
SBIT(IE_SPI0, 0xE8, 0);
SFR(IP_EX, 0xE9);
SFR(GPIO_IE, 0xC7);

//Flash SFRs
SFR16(ROM_ADDR, 0x84);
SFR(ROM_ADDR_L, 0x84);
SFR(ROM_ADDR_H, 0x85);
SFR16(ROM_DATA, 0x8E);
SFR(ROM_DATA_L, 0x8E);
SFR(ROM_DATA_H, 0x8F);
SFR(ROM_CTRL, 0x86);

// Port SFRs
SFR(P1, 0x90);
SBIT(P10, 0x90, 0);
SBIT(P11, 0x90, 1);
SBIT(P12, 0x90, 2);
SBIT(P13, 0x90, 3);
SBIT(P14, 0x90, 4);
SBIT(P15, 0x90, 5);
SBIT(P16, 0x90, 6);
SBIT(P17, 0x90, 7);
SFR(P1_MOD_OC, 0x92);
SFR(P1_DIR_PU, 0x93);
SFR(P2, 0xA0);
SFR(P3, 0xB0);
SBIT(P30, 0xB0, 0);
SBIT(P31, 0xB0, 1);
SBIT(P32, 0xB0, 2);
SBIT(P33, 0xB0, 3);
SBIT(P34, 0xB0, 4);
SBIT(P35, 0xB0, 5);
SBIT(P36, 0xB0, 6);
SBIT(P37, 0xB0, 7);
SFR(P3_MOD_OC, 0x96);
SFR(P3_DIR_PU, 0x97);
SFR(PIN_FUNC, 0xC6);
SFR(XBUS_AUX, 0xA2);

// Timer0/1 SFRs
SFR(TCON,0x88);
SBIT(TF1, 0x88, 7);
SBIT(TR1, 0x88, 6);
SBIT(TF0, 0x88, 5);
SBIT(TR0, 0x88, 4);
SBIT(IE1, 0x88, 3);
SBIT(IT1, 0x88, 2);
SBIT(IE0, 0x88, 1);
SBIT(IT0, 0x88, 0);
SFR(TMOD,0x89);
SFR(TL0,0x8A);
SFR(TL1,0x8B);
SFR(TH0,0x8C);
SFR(TH1,0x8D);

// Timer2 SFRs
SFR(T2CON, 0xC8);
SBIT(TF2, 0xC8, 7);
SBIT(CAP1F, 0xC8, 7);
SBIT(EXF2, 0xC8, 6);
SBIT(RCLK, 0xC8, 5);
SBIT(TCLK, 0xC8, 4);
SBIT(EXEN2, 0xC8, 3);
SBIT(TR2, 0xC8, 2);
SBIT(C_T2, 0xC8, 1);
SBIT(CP_RL2, 0xC8, 0);
SFR(T2MOD, 0xC9);
SFR16(RCAP2, 0xCA);
SFR(RCAP2L, 0xCA);
SFR(RCAP2H, 0xCB);
SFR16(T2COUNT, 0xCC);
SFR(TL2, 0xCC);
SFR(TH2, 0xCD);
SFR16(T2CAP1, 0xCE);
SFR(T2CAP1L, 0xCE);
SFR(T2CAP1H, 0xCF);

// PWM SFRs
SFR(PWM_DATA2, 0x9B);
SFR(PWM_DATA1, 0x9C);
SFR(PWM_CTRL, 0x9D);
SFR(PWM_CK_SE, 0x9E);

// UART0 SFRs
SFR(SCON, 0x98);
SBIT(SM0, 0x98, 7);
SBIT(SM0, 0x98, 7);
SBIT(SM1, 0x98, 6);
SBIT(SM2, 0x98, 5);
SBIT(REN, 0x98, 4);
SBIT(TB8, 0x98, 3);
SBIT(RB8, 0x98, 2);
SBIT(TI, 0x98, 1);
SBIT(RI, 0x98, 0);
SFR(SBUF, 0x99);

// UART1 SFRs
SFR(SCON1, 0xC0);
SBIT(U1SM0, 0xC0, 7);
SBIT(U1SMOD, 0xC0, 5);
SBIT(U1REN, 0xC0, 4);
SBIT(U1TB8, 0xC0, 3);
SBIT(U1RB8, 0xC0, 2);
SBIT(U1TI, 0xC0, 1);
SBIT(U1RI, 0xC0, 0);
SFR(SBUF1, 0xC1);
SFR(SBAUD1, 0xC2);

// SPI SFRs
SFR(SPI0_STAT, 0xF8);
SBIT(S0_FST_ACT, 0xF8, 7);
SBIT(S0_IF_OV, 0xF8, 6);
SBIT(S0_IF_FIRST, 0xF8, 5);
SBIT(S0_IF_BYTE, 0xF8, 4);
SBIT(S0_FREE, 0xF8, 3);
SBIT(S0_T_FIFO, 0xF8, 2);
SBIT(S0_R_FIFO, 0xF8, 0);
SFR(SPI0_DATA, 0xF9);
SFR(SPI0_CTRL, 0xFA);
SFR(SPI0_CK_SE, 0xFB);
SFR(SPI0_SETUP, 0xFC);

// ADC SFRs
SFR(ADC_CTRL, 0x80);
SBIT(CMPO, 0x80, 7);
SBIT(CMP_IF, 0x80, 6);
SBIT(ADC_IF, 0x80, 5);
SBIT(ADC_START, 0x80, 4);
SBIT(CMP_CHAN, 0x80, 3);
SBIT(ADC_CHAN1, 0x80, 1);
SBIT(ADC_CHAN0, 0x80, 0);
SFR(ADC_CFG, 0x9A);
SFR(ADC_DATA, 0x9F);

// Touch SFRs
SFR(TKEY_CTRL, 0xC3);
SFR16(TKEY_DAT, 0xC4);
SFR(TKEY_DATL, 0xC4);
SFR(TKEY_DATH, 0xC5);

// USB SFRs
SFR(USB_C_CTRL, 0x91);
SFR(USB_CTRL, 0xE2);
SFR(UDEV_CTRL, 0xD1);
SFR(USB_DEV_AD, 0xE3);
SFR(USB_MIS_ST, 0xDA);
SFR(USB_RX_LEN, 0xDB);
SFR(USB_INT_EN, 0xE1);
SFR(USB_INT_FG, 0xD8);
SBIT(U_IS_NAK, 0xD8, 7);
SBIT(U_TOG_OK, 0xD8, 6);
SBIT(U_SIE_FREE, 0xD8, 5);
SBIT(UIF_FIFO_OV, 0xD8, 4);
SBIT(UIF_HST_SOF, 0xD8, 3);
SBIT(UIF_SUSPEND, 0xD8, 2);
SBIT(UIF_TRANSFER, 0xD8, 1);
SBIT(UIF_DETECT, 0xD8, 0);
SBIT(UIF_BUS_RST, 0xD8, 0);
SFR(USB_INT_ST, 0xD9);
SFR(UEP4_1_MOD, 0xEA);
SFR(UEP2_3_MOD, 0xEB);
SFR(UEP0_CTRL, 0xDC);
SFR(UEP0_T_LEN, 0xDD);
SFR(UEP1_CTRL, 0xD2);
SFR(UEP1_T_LEN, 0xD3);
SFR(UEP2_CTRL, 0xD4);
SFR(UEP2_T_LEN, 0xD5);
SFR(UEP3_CTRL, 0xD6);
SFR(UEP3_T_LEN, 0xD7);
SFR(UEP4_CTRL, 0xDE);
SFR(UEP4_T_LEN, 0xDF);
SFR16(UEP0_DMA, 0xEC);
SFR(UEP0_DMA_L, 0xEC);
SFR(UEP0_DMA_H, 0xED);
SFR16(UEP1_DMA, 0xEE);
SFR(UEP1_DMA_L, 0xEE);
SFR(UEP1_DMA_H, 0xEF);
SFR16(UEP2_DMA, 0xE4);
SFR(UEP2_DMA_L, 0xE4);
SFR(UEP2_DMA_H, 0xE5);
SFR16(UEP3_DMA, 0xE6);
SFR(UEP3_DMA_L, 0xE6);
SFR(UEP3_DMA_H, 0xE7);

// Interrupt vectors
#define INT_NO_INT0 0
#define INT_NO_TMR0 1
#define INT_NO_INT1 2
#define INT_NO_TMR1 3
#define INT_NO_UART0 4
#define INT_NO_TMR2 5
#define INT_NO_SPI0 6
#define INT_NO_TKEY 7
#define INT_NO_USB 8
#define INT_NO_ADC 9
#define INT_NO_UART1 10
#define INT_NO_PWMX 11
#define INT_NO_GPIO 12
#define INT_NO_WDOG 13

#endif
