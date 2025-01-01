#include <ch552.h>
#include <utils.h>
#include <ssd1306.h>

void main(void) {
    init();
    oled_init();

    oled_print("* CH552 with OLED   *");
    oled_cursor(0,1);
    oled_print("---------------------");
    oled_cursor(0,2);
    oled_print("Nicola Strappaazzon");

    while(1) {}
}
