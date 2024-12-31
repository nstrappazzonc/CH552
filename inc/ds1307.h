#ifndef DS1307_h
#define DS1307_h

#pragma once
#include <stdbool.h>
// #include <8051.h>
#include <stdint.h>
// #include "i2c.h"

typedef struct {
  uint8_t second;
  uint8_t minute;
  uint8_t hour;
  uint8_t day;
  uint8_t date;
  uint8_t month;
  uint8_t year;
}rtc_t;

// void rtc_set(rtc_t*);
void rtc_init(void);
void rtc_get(rtc_t*);
// uint8_t last_digit(uint8_t n);
// uint8_t first_digit(uint8_t n);
// uint8_t bcd_to_dec(uint8_t val);


void i2c_init(void);
void i2c_delay2(void);
void i2c_start2(void);
void i2c_stop2(void);
void i2c_write2(uint8_t data);
// uint8_t i2c_read2(void);
uint8_t i2c_read2(uint8_t ack);
// bool i2c_read_ack2(void);
// bool i2c_read_nak2(void);

#endif
