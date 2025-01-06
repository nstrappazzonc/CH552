#ifndef DS1307_h
#define DS1307_h

#pragma once
#include <stdbool.h>
#include <stdint.h>

typedef struct {
  uint8_t second;
  uint8_t minute;
  uint8_t hour;
  uint8_t week_day;
  uint8_t day;
  uint8_t month;
  uint8_t year;
} rtc_t;

// void rtc_set(rtc_t*);
void rtc_init(void);
void rtc_set(rtc_t *);
void rtc_get(rtc_t *);
void i2c_init(void);
void i2c_delay2(void);
void i2c_start2(void);
void i2c_stop2(void);
void i2c_write2(uint8_t data);
uint8_t i2c_read2(uint8_t ack);

#endif
