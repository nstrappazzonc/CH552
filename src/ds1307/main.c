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

    rtc.hour     = 0x13;   // Hour:     13
    rtc.minute   = 0x11;   // Minute:   11
    rtc.second   = 0x00;   // Second:   0
    rtc.day      = 0x01;   // Day:      1
    rtc.month    = 0x01;   // Month:    January
    rtc.year     = 0x24;   // Year:     24
    rtc.week_day = 0x03;   // Week day: Friday, 5th day of week considering monday as first day.
                           //           0    1    2    3    4    5    6
                           //           Sun, Mon, Tue, Wed, Thu, Fri, Sat

    rtc_set(&rtc);

    while(1) {
        rtc_get(&rtc);
        sprintf(buffer, "  %02x/%02x/%02x %02x:%02x:%02x", rtc.year, rtc.month, rtc.day, rtc.hour, rtc.minute, rtc.second);
        oled_set_cursor(3, 0);
        oled_print(buffer);
        delay(1000);
    }
}
