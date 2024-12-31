#include <ch552.h>
#include <utils.h>
#include <oled.h>

void main(void) {
    init();
    oled_init();
    oled_print("* CH552 with OLED   *");
    oled_print("---------------------");
    oled_print("Nicola Strappaazzon\n");
    oled_print("!@#$%^&*()_-+=<>,.?/\n");
    oled_print("\n");

    while(1) {}
}
