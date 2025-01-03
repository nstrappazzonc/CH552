#pragma once
#include <stdint.h>

void I2C_init(void);            // I2C init function
void I2C_start(uint8_t addr);   // I2C start transmission
void I2C_restart(uint8_t addr); // I2C restart transmission
void I2C_stop(void);            // I2C stop transmission
void I2C_write(uint8_t data);   // I2C transmit one data byte to the slave
uint8_t I2C_read(uint8_t ack);  // I2C receive one data byte from the slave
