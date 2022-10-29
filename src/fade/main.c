#include <ch552.h>
#include <utils.h>
#include <pwm.h>

void main(void) {
    int i = 0;

    PWMSetClk(4);
    PWMForceClear();
    PWMCancelClear();
    PWM1PinAlter();
    PWM1OutEnable();
    // PWM1OutPolarHighAct();

    while(1) {
        for (i = 0 ;i < 255; i++) {
            PWMSetData1(i);
            delay(1);
        }
        for (i = 255 ;i > 0; i--) {
            PWMSetData1(i);
            delay(1);
        }
        delay(1);
    }
}
