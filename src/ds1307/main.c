#include <ch552.h>
#include <utils.h>
#include <ds1307.h>
#include <oled.h>
#include <stdint.h>
#include <stdio.h>

void main(void) {
    rtc_t rtc;
    unsigned char buffer[8];

    init();
    oled_init();
    rtc_init();

    while(1) {
        rtc_get(&rtc);
        sprintf(buffer, "%02x:%02x:%02x", rtc.hour, rtc.minute, rtc.second);
        // oled_clear();
        oled_set_position(1, 0);
        oled_print(buffer);
        delay(1000);
    }
}
