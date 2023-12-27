#include <stdint.h>
#include "ch552.h"
#include "utils.h"

#define bUART0_PIN_X      0x10      // UART0 alternate pin enable: 0=RXD0/TXD0 on P3.0/P3.1, 1=RXD0/TXD0 on P1.2/P1.3
#define bT1_GATE          0x80      // gate control of timer1: 0=timer1 run enable while TR1=1, 1=timer1 run enable while P3.3 (INT1) pin is high and TR1=1
#define bT1_CT            0x40      // counter or timer mode selection for timer1: 0=timer, use internal clock, 1=counter, use P3.5 (T1) pin falling edge as clock
#define bT1_M1            0x20      // timer1 mode high bit
#define MASK_T1_MOD       0x30      // bit mask of timer1 mode
#define bTMR_CLK          0x80      // fastest internal clock mode for timer 0/1/2 under faster clock mode: 0=use divided clock, 1=use original Fsys as clock without dividing
#define bT1_CLK           0x20      // timer1 internal clock frequency selection: 0=standard clock, Fsys/12, 1=faster clock, Fsys/4 if bTMR_CLK=0 or Fsys if bTMR_CLK=1
#define SMOD              0x80

// #define FREQ_SYS 24000000
#define UART0_BAUDRATE 9600

void UART0Init();
void UART0Send(uint8_t);
void UART0SendString(char*);

void main(void) {
    init();

    UART0Init();

    while(1){
        UART0SendString("Hello from CH552T with CH340C\n\r");
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
    // ES = 1;  // Interrupt enable
    // EA = 1;
}

inline void UART0Send(uint8_t byte) __critical{
    SBUF = byte;
    while(TI ==0); // Wait for done
    TI = 0;

    return;
}

void UART0SendString(char* string){
    while(*string!='\0'){
        UART0Send(*string);
        string++;
    }

    return;
}
