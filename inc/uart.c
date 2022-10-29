#include "ch554.h"
#include "uart.h"

// printf will use putchar function
#pragma callee_saves putchar
// putchar takes a single argument:
// char, or int for sdcc version 3.7.0 and later
// in both cases, only one byte, DPL, is copied to SBUF
void putchar()
{
    /*
    while (!TI);            // assumes UART is initialized
    TI = 0;
    SBUF = c & 0xFF;
    return c;
    */
    __asm
    1$:
    jnb _TI, 1$
    clr _TI

    mov _SBUF, dpl
    __endasm;
}

#pragma callee_saves getchar
// getchar returns char or int depending on the sdcc version
// lie to sdcc and declare it as void but return in DPL
void getchar()
{
    /*
    while(!RI);             // assumes UART is initialized
    RI = 0;
    return SBUF;
    */
    __asm
    1$:
    jnb _RI, 1$
    clr _RI

    mov dpl, _SBUF
    mov dph, #0
    __endasm;
}
