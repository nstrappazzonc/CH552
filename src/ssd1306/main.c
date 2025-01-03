#include <ch552.h>
#include <utils.h>
#include <ssd1306.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>

void float_to_string(char* buffer, float num) {
    int int_part = (int) num;                   // Parte entera del número
    int decimal_part = (int)((num - int_part) * 100);  // Parte decimal, con dos decimales

    sprintf(buffer, "%d.%02d", int_part, decimal_part);  // Formatear en buffer
}

void main(void) {
    init();
    oled_init();

    oled_print("* CH552 with OLED   *");
    oled_cursor(0,1);
    oled_print("---------------------");
    oled_cursor(0,2);
    oled_print("Nicola Strappaazzon");
    oled_cursor(0,3);

    char buffer[10];
    float_to_string(buffer, 3.14159);
    oled_print(buffer);

    while(1) {}
}
