#include <ch552.h>
#include <utils.h>
#include <pwm.h>

void main(void) {
    init();

    int i = 0;

    PWMSetClk(4);
    PWMForceClear();
    PWMCancelClear();

    // PWM1: P3.0:
    // ===========
    PWM1PinAlter();
    PWM1OutEnable();

    // PWM2: P3.1:
    // ===========
    // PWM2PinAlter();
    // PWM2OutEnable();

    while(1) {
        for (i = 40 ;i < 255; i++) {
            PWMSetData1(i);
            // PWMSetData2(i);
            delay(1);
        }
        for (i = 255 ;i > 10; i--) {
            PWMSetData1(i);
            // PWMSetData2(i);
            delay(1);
        }
        delay(1);
    }
}
