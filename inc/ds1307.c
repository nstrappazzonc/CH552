#include "utils.h"
#include "gpio.h"
#include "ds1307.h"

#define DS1307_ADDRESS 0x68

#define C_Ds1307ReadMode_U8   0xD1u  // DS1307 ID
#define C_Ds1307WriteMode_U8  0xD0u  // DS1307 ID
#define C_Ds1307ControlRegAddress_U8 0x07u
#define C_Ds1307SecondRegAddress_U8   0x00u   // Address to access Ds1307 SEC register

#define PIN_SDA P16
#define PIN_SCL P17

#define I2C_DELAY_H() __asm__("sjmp .+2");++SAFE_MOD      // delay 6-7 clock cycles
#define I2C_DELAY_L() __asm__("sjmp .+2");++SAFE_MOD      // delay 6-7 clock cycles

#define I2C_SDA_HIGH()  PIN_high(PIN_SDA)   // release SDA -> pulled HIGH by resistor
#define I2C_SDA_LOW()   PIN_low(PIN_SDA)    // SDA LOW     -> pulled LOW  by MCU
#define I2C_SCL_HIGH()  PIN_high(PIN_SCL)   // release SCL -> pulled HIGH by resistor
#define I2C_SCL_LOW()   PIN_low(PIN_SCL)    // SCL LOW     -> pulled LOW  by MCU
#define I2C_SDA_READ()  PIN_read(PIN_SDA)   // read SDA pin
#define I2C_CLOCKOUT()  I2C_DELAY_L();I2C_SCL_HIGH();I2C_DELAY_H();I2C_DELAY_H();I2C_SCL_LOW()

// I2C macros
#define I2C_SDA_HIGH()  PIN_high(PIN_SDA)   // release SDA -> pulled HIGH by resistor
#define I2C_SDA_LOW()   PIN_low(PIN_SDA)    // SDA LOW     -> pulled LOW  by MCU
#define I2C_SCL_HIGH()  PIN_high(PIN_SCL)   // release SCL -> pulled HIGH by resistor
#define I2C_SCL_LOW()   PIN_low(PIN_SCL)    // SCL LOW     -> pulled LOW  by MCU
#define I2C_SDA_READ()  PIN_read(PIN_SDA)   // read SDA pin
#define I2C_CLOCKOUT()  I2C_DELAY_L();I2C_SCL_HIGH();I2C_DELAY_H();I2C_DELAY_H();I2C_SCL_LOW()

void rtc_init(void) {
    i2c_init();
    i2c_start2();
    i2c_write2(C_Ds1307WriteMode_U8);
    i2c_write2(C_Ds1307ControlRegAddress_U8);
    i2c_write2(0x00);
    i2c_stop2();
}

void rtc_get(rtc_t* rtc) {    
    i2c_start2();
    i2c_write2(C_Ds1307WriteMode_U8);      // connect to DS1307 by sending its ID on I2c Bus
    i2c_write2(C_Ds1307SecondRegAddress_U8); // Request sec RAM address at 00H
    i2c_stop2();

    i2c_start2();
    i2c_write2(C_Ds1307ReadMode_U8);
    rtc->second = i2c_read2(1);
    rtc->minute = i2c_read2(1);
    rtc->hour   = i2c_read2(1);
    rtc->day    = i2c_read2(1);
    rtc->date   = i2c_read2(1);
    rtc->month  = i2c_read2(1);
    rtc->year   = i2c_read2(0);
    i2c_stop2();
}

void i2c_init(void) {
    PIN_output_OD(PIN_SDA);                   // set SDA pin to open-drain OUTPUT
    PIN_output_OD(PIN_SCL);                   // set SCL pin to open-drain OUTPUT
    PIN_high(PIN_SDA);
    PIN_high(PIN_SCL);
}

void i2c_start2(void) {
    I2C_SDA_LOW();                            // start condition: SDA goes LOW first
    I2C_DELAY_H();                            // delay
    I2C_SCL_LOW();                            // start condition: SCL goes LOW second
}

void i2c_stop2(void) {
    I2C_SDA_LOW();                            // prepare SDA for LOW to HIGH transition
    I2C_DELAY_H();                            // delay
    I2C_SCL_HIGH();                           // stop condition: SCL goes HIGH first
    I2C_DELAY_H();                            // delay
    I2C_SDA_HIGH();                           // stop condition: SDA goes HIGH second
}

void i2c_write2(uint8_t data) {
  uint8_t i;
  for(i=8; i; i--, data<<=1) {              // transmit 8 bits, MSB first
    (data & 0x80) ? (I2C_SDA_HIGH()) : (I2C_SDA_LOW());  // SDA HIGH if bit is 1
    I2C_CLOCKOUT();                         // clock out -> slave reads the bit
  }
  I2C_SDA_HIGH();                           // release SDA for ACK bit of slave
  I2C_DELAY_H();                            // delay
  I2C_DELAY_H();                            // delay
  I2C_CLOCKOUT();                           // 9th clock pulse is for the ignored ACK bit
}

uint8_t i2c_read2(uint8_t ack) {
  uint8_t i;
  uint8_t data = 0;                         // variable for the received byte
  I2C_SDA_HIGH();                           // release SDA -> will be toggled by slave
  for(i=8; i; i--) {                        // receive 8 bits
    data <<= 1;                             // bits shifted in right (MSB first)
    I2C_DELAY_H();                          // delay
    I2C_DELAY_L();                          // delay
    I2C_SCL_HIGH();                         // clock HIGH
    if(I2C_SDA_READ()) data |= 1;           // read bit
    I2C_SCL_LOW();                          // clock LOW -> slave prepares next bit
  }
  if(ack) I2C_SDA_LOW();                    // pull SDA LOW to acknowledge (ACK)
  I2C_DELAY_H();                            // delay
  I2C_DELAY_H();                            // delay
  I2C_CLOCKOUT();                           // clock out -> slave reads ACK bit
  return data;                              // return the received byte
}
