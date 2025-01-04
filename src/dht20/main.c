#include <ch552.h>
#include <ssd1306.h>
#include <stdio.h>
#include <utils.h>
#include <bmp280.h>

unsigned char buffer[13];

void main(void) {
    init();
    I2C_init();
    oled_init();

    bmp280_init();
    bmp280_calibration(BMP280_ADDR);
    delay(1000);

    while(1) {
        if (bmp280_connected()) {
            oled_cursor(0,0);
            oled_print("si");
        } else {
            oled_cursor(0,0);
            oled_print("no");
        }

        // int32_t tmp = bmp280_temperature_raw(BMP280_ADDR);
        // sprintf(buffer, "Temp raw: %ld", tmp);
        // oled_cursor(0,1);
        // oled_print(buffer);

        char* tmpC = bmp280_temperature(BMP280_ADDR);
        sprintf(buffer, "Temp: %sC", tmpC);
        oled_cursor(0,2);
        oled_print(buffer);

        delay(1000);
    }
}

