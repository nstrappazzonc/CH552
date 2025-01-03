#include "bmp280.h"

uint16_t dig_T1;
int16_t dig_T2;
int16_t dig_T3;

void bmp280_init(void) {
    // Escribimos 0x27 en el registro CTRL_MEAS (0xF4) para configurar el modo normal
    I2C_start(BMP280_ADDR);                  // Iniciar la transmisión con la dirección del dispositivo
    I2C_write(0xF4);                         // Dirección del registro CTRL_MEAS
    I2C_write(0x27);                         // Escribir 0x27 (Normal mode, 1x res. para temp. y pres.)
    I2C_stop();                              // Detener la transmisión
}

uint8_t bmp280_read_array(uint8_t device_address, uint8_t register_address) {
    I2C_start(device_address << 1);
    I2C_write(register_address);
    I2C_restart((device_address << 1) | 1);
    uint8_t data = I2C_read(0);
    I2C_stop();

    return data;
}

bool bmp280_connected(void) {
    return bmp280_read_array(BMP280_ADDR, BMP280_REG_CHIP_ID) == BMP280_DEF_CHIP_ID;
}

int32_t bmp280_temperature_raw(uint8_t device_address) {
    uint8_t msb, lsb, xlsb;

    I2C_start(device_address << 1);
    I2C_write(BMP280_TEMP_MSB);
    I2C_restart((device_address << 1) | 1);

    msb  = I2C_read(1);
    lsb  = I2C_read(1);
    xlsb = I2C_read(0);

    I2C_stop();

    return (int32_t)((((uint32_t)msb) << 12) + (((uint32_t)lsb) << 4) + (((uint32_t)xlsb) >> 4));
}

void bmp280_calibration(uint8_t device_address) {
    // I2C_start(device_address << 1);
    // I2C_write(BMP280_TEMP_CAL);
    // I2C_restart((device_address << 1) | 1);

    // uint8_t dataLSB = bmp280_read_array(device_address, 0x88);
    // uint8_t dataMSB = bmp280_read_array(device_address, 0x88 + 1);
    // dig_T1 = (uint16_t)((((uint16_t)dataMSB) << 8) + (uint16_t)dataLSB);

    // uint16_t dataLSB2 = bmp280_read_array(device_address, 0x8A);
    // uint16_t dataMSB2 = bmp280_read_array(device_address, 0x8A + 1);
    // dig_T2 = (int16_t)((((int16_t)dataMSB2) << 8) + (int16_t)dataLSB2);

    // uint16_t dataLSB3 = bmp280_read_array(device_address, 0x8C);
    // uint16_t dataMSB3 = bmp280_read_array(device_address, 0x8C + 1);
    // dig_T3 = (int16_t)((((int16_t)dataMSB3) << 8) + (int16_t)dataLSB3);

    // Registro de calibración para dig_T1, dig_T2, dig_T3
    dig_T1 = bmp280_read_array(device_address, 0x88) | (bmp280_read_array(device_address, 0x89) << 8);
    dig_T2 = bmp280_read_array(device_address, 0x8A) | (bmp280_read_array(device_address, 0x8B) << 8);
    dig_T3 = bmp280_read_array(device_address, 0x8C) | (bmp280_read_array(device_address, 0x8D) << 8);

    // dig_T1 = bmp280_read_array(device_address, 0x88) //(I2C_read(1) | (I2C_read(1) << 8));  // 0x88-0x89
    // dig_T2 = bmp280_read_array(device_address, 0x8A) //(I2C_read(1) | (I2C_read(1) << 8));  // 0x8A-0x8B
    // dig_T3 = bmp280_read_array(device_address, 0x8C) //(I2C_read(1) | (I2C_read(1) << 8));  // 0x8C-0x8D

    // I2C_stop();
}

char* bmp280_temperature(uint8_t device_address) {
    int32_t temp_raw = bmp280_temperature_raw(device_address);
    int32_t var1, var2, T;

    // Fórmula de compensación para la temperatura
    var1 = ((((temp_raw >> 3) - ((int32_t)dig_T1 << 1))) * ((int32_t)dig_T2)) >> 11;
    var2 = (((((temp_raw >> 4) - ((int32_t)dig_T1)) * ((temp_raw >> 4) - ((int32_t)dig_T1))) >> 12) * ((int32_t)dig_T3)) >> 14;

    T = var1 + var2;
    float temperature = (float)(((T * 5 + 128) >> 8) / 100);

    // float temperature = 23.1415914159;
    char buffer[5];
    float_to_string(buffer, temperature);

    return buffer;
}

void float_to_string(char* buffer, float num) {
    int int_part = (int) num;                   // Parte entera del número
    int decimal_part = (int)((num - int_part) * 100);  // Parte decimal, con dos decimales

    sprintf(buffer, "%02d.%02d", int_part, decimal_part);  // Formatear en buffer
}
