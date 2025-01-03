#include "bmp280.h"

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
