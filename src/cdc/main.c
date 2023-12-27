#include <stdint.h>
#include "ch552.h"
#include "utils.h"

#define UART0_BAUDRATE 9600

void UART0Init();
uint8_t UART0Read();
void UART0Write(uint8_t);
void UART0WriteString(char*);

void main(void) {
    init();

    UART0Init();
    UART0WriteString("Hello from CH552T with CH340C\n\r");
    UART0WriteString("Type any char to reply:\n\r");
    while(1){
        UART0Write(UART0Read());
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

void UART0Write(uint8_t byte) {
    SBUF = byte;
    while(TI ==0);
    TI = 0;

    return;
}

uint8_t UART0Read() {
    while(RI == 0);
    RI = 0;
    return SBUF;
}

void UART0WriteString(char* string) {
    while(*string!='\0'){
        UART0Write(*string);
        string++;
    }

    return;
}
