#include <ch552.h>
#include <utils.h>
#include "stdio.h"

#define UART0_BAUDRATE 9600

void ADCInit();
void ADCChannel(uint8_t);
void UART0Init();
void UART0Write(uint8_t);
void UART0WriteString(char*);

void main(void) {
    init();
    UART0Init();
    ADCInit();
    ADCChannel(0);
    printf("ADC example AIN%02x\n\r", 0);

    while(1) {
        ADC_START = 1;
        while(ADC_START == 0);
        printf("DATA: %03d\n\r", ADC_DATA);
        delay(1000);
    }
}

void ADCInit() {
    ADC_CFG |= bADC_EN;
    ADC_CFG &= ~bADC_CLK;
    ADC_CFG |= bCMP_EN;
}

void ADCChannel(uint8_t ch) {
    switch (ch){
        case 0:
            ADC_CHAN1 = 0;
            ADC_CHAN0 = 0;
            P1_DIR_PU |= bAIN0;
            break;
        case 1:
            ADC_CHAN1 = 0;
            ADC_CHAN0 = 1;
            P1_DIR_PU |= bAIN1;
            break;
        case 2:
            ADC_CHAN1 = 1;
            ADC_CHAN0 = 0;
            P1_DIR_PU |= bAIN2;
            break;
        case 3:
            ADC_CHAN1 = 1;
            ADC_CHAN0 = 0;
            P1_DIR_PU |= bAIN3;
            break;
    }
}


void UART0Init(){
    PIN_FUNC |= (1<<bUART0_PIN_X); // UART0 use P3.0 (RX) and P3.1 (TX)
    SM0 = 0;
    SM1 = 1;
    SM2 = 0;
    RCLK = 0; // UART Receive clock
    TCLK = 0; // UART Transmit clock
    PCON |= SMOD;
    TMOD = TMOD & ~ bT1_GATE & ~ bT1_CT & ~ MASK_T1_MOD | bT1_M1; // 8 bits async mode, baudrate is provided by Timer1
    T2MOD = T2MOD | bTMR_CLK | bT1_CLK;
    TH1 = (256 - (FREQ_SYS+(16/UART0_BAUDRATE/2))/16/UART0_BAUDRATE);
    TR1 = 1; // Timer1 start
    TI = 0;
    REN = 1; // UART0 Receive enable
}

int putchar(int c) {
    SBUF = c;
    while (TI == 0);
    TI = 0;

    return c;
}

int getchar() {
    while(!RI);
    RI = 0;
    return SBUF;
}
