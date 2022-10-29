#include <ch552.h>
#include <utils.h>

// SBIT(LED, P3, P30);

void main(void) {
    init();

    P3_MOD_OC &= ~(1<<P30);
    P3_DIR_PU |=  (1<<P30);

    while(1) {
        delay(1000);
        P30 =! P30;
    }
}
