#ifndef __BMP280_H__
#define __BMP280_H__

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <i2c.h>

#define BMP280_ADDR        0x76 // Can be 0x76 or 0x77.
#define BMP280_REG_CHIP_ID 0xD0 // Register of chip id.
#define BMP280_DEF_CHIP_ID 0x58 // Default value of chip id.
#define BMP280_TEMP_MSB    0xFA // MSB (Most Significant Byte): Es el byte más significativo.
#define BMP280_TEMP_LSB    0xFB // LSB (Least Significant Byte): Es el byte menos significativo.
#define BMP280_TEMP_XLSB   0xFC // XLSB (Extended Least Significant Byte): Es un byte adicional que proporciona una precisión extra en los bits más bajos.
#define BMP280_TEMP_CAL    0x88

void bmp280_init(void);
bool bmp280_connected(void);
uint8_t bmp280_read_array(uint8_t, uint8_t);
int32_t bmp280_temperature_raw(uint8_t);
char* bmp280_temperature(uint8_t);
void bmp280_calibration(uint8_t);
void float_to_string(char*, float);

#endif
