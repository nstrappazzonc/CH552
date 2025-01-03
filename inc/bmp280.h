#ifndef __BMP280_H__
#define __BMP280_H__

#pragma once
#include <stdbool.h>
#include <stdint.h>
#include <i2c.h>

#define BMP280_ADDR        0x76 // Can be 0x76 or 0x77.
#define BMP280_REG_CHIP_ID 0xD0 // Register of chip id.
#define BMP280_DEF_CHIP_ID 0x58 // Default value of chip id.
#define BMP280_TEMP_MSB    0xFA // MSB (Most Significant Byte): Es el byte más significativo.
#define BMP280_TEMP_LSB    0xFB // LSB (Least Significant Byte): Es el byte menos significativo.
#define BMP280_TEMP_XLSB   0xFC // XLSB (Extended Least Significant Byte): Es un byte adicional que proporciona una precisión extra en los bits más bajos.

bool bmp280_connected(void);
uint8_t bmp280_read_array(uint8_t deviceAddress, uint8_t startRegisterAddress);

#endif


// Registros del BMP280
// #define BMP280_TEMP_MSB 0xFA
// #define BMP280_TEMP_LSB 0xFB
// #define BMP280_TEMP_XLSB 0xFC
// #define BMP280_CALIB_TEMP 0x88

// uint16_t dig_T1;
// int16_t dig_T2, dig_T3;
