#include <ch552.h>
#include <utils.h>

SBIT(LED, P1, P17);
SBIT(BUTTON, P1, P15);

void main(void) {
    init();

    P1_MOD_OC &= ~(1<<P17);
    P1_DIR_PU |=  (1<<P17);

    LED = 0;    // Set led to OFF initially.
    BUTTON = 0; // Set button pin as input.

    while(1) {
        if(BUTTON == 1 ) {
            LED = 1;
        }

        LED = 0;
    }
}
