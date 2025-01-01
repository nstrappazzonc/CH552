#include <ch552.h>
#include <utils.h>
#include <ds1307.h>
#include <ssd1306.h>
#include <stdint.h>
#include <stdio.h>

void main(void) {
    rtc_t rtc;
    unsigned char buffer[13];

    init();
    oled_init();
    rtc_init();

    while(1) {
        rtc_get(&rtc);
        sprintf(buffer, "  %02x/%02x/%02x %02x:%02x:%02x", rtc.year, rtc.month, rtc.date, rtc.hour, rtc.minute, rtc.second);
        oled_set_cursor(3, 0);
        oled_print(buffer);
        delay(1000);
    }
}
