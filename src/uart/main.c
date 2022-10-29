// #include <intrins.h>
// #include <stdint.h>
#include <stdio.h>
// #include <string.h>
#include <ch554.h>
// #include <uart.h>

// /*
//  * Redirect stdout to UART0
//  */
// int putchar(int c) {
//     uart0_write(c);
//     return 0;
// }

// int putchar(int c) {
//     while (!TI);
//     TI = 0;
//     SBUF = c & 0xFF;
//     return c;
// }

// int getchar() {
//     while(!RI);
//     RI = 0;
//     return SBUF;
// }

// /*
//  * Redirect stdin to UART0
//  */
// int getchar() {
//     return uart0_read();
// }


void main() {
    TMOD = 0x20; /* TMOD: timer 1, mode 2, 8-bit reload */ //Timer1 Mode2, 8 bit auto reload
    SCON = 0x50;   /* SCON: mode 1, 8-bit UART, enable rcvr */ //8 Data bit, 1 start bit, 1 stop bit
    TH1  = 0xFD;    //9600 Baud
    TL1  = 0x00;
    TR1  = 1;
	
	while (1) {
        printf("Hello World!\n");
    }
}
