#include <ch552.h>
#include <utils.h>

#define LED P30

void main(void) {
    init();

    P3_MOD_OC &= ~(1<<LED);
    P3_DIR_PU |=  (1<<LED);

    while(1) {
        // Option 1: 
        // delay(1000);
        // LED = 0;
        // delay(1000);
        // LED = 1;

        // Option 2:
        delay(1000);
        LED =! LED;
    }
}
