#ifndef OLED_h
#define OLED_h

#pragma once
#include <stdint.h>
#include "i2c.h"

#define OLED_ADDR         0x78 // OLED write address (0x3C << 1).
#define OLED_COMMAND      0x00 // Set command mode.
#define OLED_DAT_MODE     0x40 // Set data mode.
#define OLED_MEMORYMODE   0x20 // Set memory addressing mode (following byte).
#define OLED_STARTLINE    0x40 // Set display start line (0x40-0x7F = 0-63).
#define OLED_CONTRAST     0x81 // Set display contrast (following byte).
#define OLED_CHARGEPUMP   0x8D // (following byte - 0x14:enable, 0x10: disable).
#define OLED_XFLIP        0xA1 // Flip display horizontally.
#define OLED_MULTIPLEX    0xA8 // Set multiplex ratio (following byte).
#define OLED_DISPLAY_ON   0xAF // Set display on.
#define OLED_PAGE         0xB0 // Set start page (following byte).
#define OLED_YFLIP        0xC8 // Flip display vertically.
#define OLED_OFFSET       0xD3 // Set display offset (y-scroll: following byte).
#define OLED_COMPINS      0xDA // Set COM pin config (following byte).

void oled_init(void);
void oled_clear(void);
void oled_write(char c);
void oled_print(char* str);
void oled_set_position(uint8_t, uint8_t);

#endif
