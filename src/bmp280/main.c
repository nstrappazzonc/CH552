#include <ch552.h>
#include <ssd1306.h>
#include <stdint.h>
#include <stdio.h>
#include <utils.h>
#include <bmp280.h>

unsigned char buffer[13];

// // Función para inicializar el BMP280
// void bmp280_init(void) {
//     I2C_start(BMP280_ADDR << 1);
//     I2C_write(BMP280_TEMP_MSB);  // Registro de control
//     // I2C_write(0x27);  // Configuración: modo normal, oversampling x1
//     I2C_stop();

//     bmp280_read_calibration();
// }

// // Función para leer los datos de calibración
// void bmp280_read_calibration(void) {
//     I2C_start(BMP280_ADDR << 1);
//     I2C_write(BMP280_CALIB_TEMP);    
//     I2C_restart((BMP280_ADDR << 1) | 1);

//     // Leer coeficientes de calibración
//     dig_T1 = (I2C_read(1) | (I2C_read(1) << 8));
//     dig_T2 = (I2C_read(1) | (I2C_read(1) << 8));
//     dig_T3 = (I2C_read(1) | (I2C_read(1) << 8));
//     I2C_stop();

//     sprintf(buffer, "Calibracion T1: %u", dig_T1);
//     oled_cursor(0,1);
//     oled_print(buffer);
//     sprintf(buffer, "Calibracion T2: %d", dig_T2);
//     oled_cursor(0,2);
//     oled_print(buffer);
//     sprintf(buffer, "Calibracion T3: %d", dig_T3);
//     oled_cursor(0,3);
//     oled_print(buffer);
// }

// int32_t bmp280_read_raw_temp(void) {
//     uint8_t msb, lsb, xlsb;
//     int32_t temp_raw;

//     I2C_start(BMP280_ADDR << 1);
//     I2C_write(BMP280_TEMP_MSB);   
//     I2C_restart((BMP280_ADDR << 1) | 1);

//     msb = I2C_read(1);
//     lsb = I2C_read(1);
//     xlsb = I2C_read(0);
//     I2C_stop();

//     sprintf(buffer, "MSB: %u", msb);
//     oled_cursor(0,1);
//     oled_print(buffer);
//     sprintf(buffer, "LSB: %u", lsb);
//     oled_cursor(0,2);
//     oled_print(buffer);
//     sprintf(buffer, "XLSB: %u", xlsb);
//     oled_cursor(0,3);
//     oled_print(buffer);

//     // Combinar los datos
//     temp_raw = ((int32_t)msb << 12) | ((int32_t)lsb << 4) | (xlsb >> 4);

//     return temp_raw;
// }

void main(void) {
    init();
    I2C_init();
    oled_init();
    // bmp280_init();
    // delay(3000);

    while(1) {
        if (bmp280_connected()) {
            oled_cursor(0,4);
            oled_print("si");
        } else {
            oled_cursor(0,4);
            oled_print("no");
        }
        // oled_cursor(0,5);
        // sprintf(buffer, "ID: %x", data);
        // oled_print(buffer);

        // bmp280_read_array()

        // int32_t tmp = bmp280_read_raw_temp();
        // sprintf(buffer, "Temp: %d", tmp);
        delay(1000);
    }
}
