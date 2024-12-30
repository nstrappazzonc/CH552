#include <ch552.h>
#include <stdint.h>
#include <utils.h>
#include <i2c.h>

// OLED definitions
#define OLED_ADDR         0x78    // OLED write address (0x3C << 1)
#define OLED_CMD_MODE     0x00    // set command mode
#define OLED_DAT_MODE     0x40    // set data mode

// OLED commands
#define OLED_COLUMN_LOW   0x00    // set lower 4 bits of start column (0x00 - 0x0F)
#define OLED_COLUMN_HIGH  0x10    // set higher 4 bits of start column (0x10 - 0x1F)
#define OLED_MEMORYMODE   0x20    // set memory addressing mode (following byte)
#define OLED_COLUMNS      0x21    // set start and end column (following 2 bytes)
#define OLED_PAGES        0x22    // set start and end page (following 2 bytes)
#define OLED_STARTLINE    0x40    // set display start line (0x40-0x7F = 0-63)
#define OLED_CONTRAST     0x81    // set display contrast (following byte)
#define OLED_CHARGEPUMP   0x8D    // (following byte - 0x14:enable, 0x10: disable)
#define OLED_XFLIP_OFF    0xA0    // don't flip display horizontally
#define OLED_XFLIP        0xA1    // flip display horizontally
#define OLED_INVERT_OFF   0xA6    // set non-inverted display
#define OLED_INVERT       0xA7    // set inverse display
#define OLED_MULTIPLEX    0xA8    // set multiplex ratio (following byte)
#define OLED_DISPLAY_OFF  0xAE    // set display off (sleep mode)
#define OLED_DISPLAY_ON   0xAF    // set display on
#define OLED_PAGE         0xB0    // set start page (following byte)
#define OLED_YFLIP_OFF    0xC0    // don't flip display vertically
#define OLED_YFLIP        0xC8    // flip display vertically
#define OLED_OFFSET       0xD3    // set display offset (y-scroll: following byte)
#define OLED_COMPINS      0xDA    // set COM pin config (following byte)

// Standard ASCII 5x8 font (chars 32 - 127)

// Font: 5x8 pixels:
// The index 11 has this values: 0x08, 0x08, 0x3E, 0x08, 0x08
// Represent char +
// 
// 0x08 => 00001000
// 0x08 => 00001000
// 0x3E => 00111110
// 0x08 => 00001000
// 0x08 => 00001000
//
__code uint8_t OLED_FONT[] = {
  0x00, 0x00, 0x00, 0x00, 0x00, //  0 => sp
  0x00, 0x00, 0x2f, 0x00, 0x00, //  1 => !
  0x00, 0x07, 0x00, 0x07, 0x00, //  2 => "
  0x14, 0x7f, 0x14, 0x7f, 0x14, //  3 => #
  0x24, 0x2a, 0x7f, 0x2a, 0x12, //  4 => $
  0x23, 0x13, 0x08, 0x64, 0x62, //  5 => %
  0x36, 0x49, 0x55, 0x22, 0x50, //  6 => &
  0x00, 0x05, 0x03, 0x00, 0x00, //  7 => '
  0x00, 0x1c, 0x22, 0x41, 0x00, //  8 => (
  0x00, 0x41, 0x22, 0x1c, 0x00, //  9 => )
  0x14, 0x08, 0x3E, 0x08, 0x14, // 10 => *
  0x08, 0x08, 0x3E, 0x08, 0x08, // 11 => +
  0x00, 0x00, 0xA0, 0x60, 0x00, // 12 => ,
  0x08, 0x08, 0x08, 0x08, 0x08, // 14 => -
  0x00, 0x60, 0x60, 0x00, 0x00, // 15 => .
  0x20, 0x10, 0x08, 0x04, 0x02, // 16 => /
  0x3E, 0x51, 0x49, 0x45, 0x3E, // 17 => 0
  0x00, 0x42, 0x7F, 0x40, 0x00, // 18 => 1
  0x42, 0x61, 0x51, 0x49, 0x46, // 19 => 2
  0x21, 0x41, 0x45, 0x4B, 0x31, // 20 => 3
  0x18, 0x14, 0x12, 0x7F, 0x10, // 21 => 4
  0x27, 0x45, 0x45, 0x45, 0x39, // 22 => 5
  0x3C, 0x4A, 0x49, 0x49, 0x30, // 23 => 6
  0x01, 0x71, 0x09, 0x05, 0x03, // 24 => 7
  0x36, 0x49, 0x49, 0x49, 0x36, // 25 => 8
  0x06, 0x49, 0x49, 0x29, 0x1E, // 26 => 9
  0x00, 0x36, 0x36, 0x00, 0x00, // 27 => :
  0x00, 0x56, 0x36, 0x00, 0x00, // 28 => ;
  0x08, 0x14, 0x22, 0x41, 0x00, // 29 => <
  0x14, 0x14, 0x14, 0x14, 0x14, // 30 => =
  0x00, 0x41, 0x22, 0x14, 0x08, // 31 => >
  0x02, 0x01, 0x51, 0x09, 0x06, // 32 => ?
  0x32, 0x49, 0x59, 0x51, 0x3E, // 33 => @
  0x7C, 0x12, 0x11, 0x12, 0x7C, // 34 => A
  0x7F, 0x49, 0x49, 0x49, 0x36, // 35 => B
  0x3E, 0x41, 0x41, 0x41, 0x22, // 36 => C
  0x7F, 0x41, 0x41, 0x22, 0x1C, // 37 => D
  0x7F, 0x49, 0x49, 0x49, 0x41, // 38 => E
  0x7F, 0x09, 0x09, 0x09, 0x01, // 39 => F
  0x3E, 0x41, 0x49, 0x49, 0x7A, // 40 => G
  0x7F, 0x08, 0x08, 0x08, 0x7F, // 41 => H
  0x00, 0x41, 0x7F, 0x41, 0x00, // 42 => I
  0x20, 0x40, 0x41, 0x3F, 0x01, // 43 => J
  0x7F, 0x08, 0x14, 0x22, 0x41, // 44 => K
  0x7F, 0x40, 0x40, 0x40, 0x40, // 45 => L
  0x7F, 0x02, 0x0C, 0x02, 0x7F, // 46 => M
  0x7F, 0x04, 0x08, 0x10, 0x7F, // 47 => N
  0x3E, 0x41, 0x41, 0x41, 0x3E, // 48 => O
  0x7F, 0x09, 0x09, 0x09, 0x06, // 49 => P
  0x3E, 0x41, 0x51, 0x21, 0x5E, // 50 => Q
  0x7F, 0x09, 0x19, 0x29, 0x46, // 51 => R
  0x46, 0x49, 0x49, 0x49, 0x31, // 52 => S
  0x01, 0x01, 0x7F, 0x01, 0x01, // 53 => T
  0x3F, 0x40, 0x40, 0x40, 0x3F, // 54 => U
  0x1F, 0x20, 0x40, 0x20, 0x1F, // 55 => V
  0x3F, 0x40, 0x38, 0x40, 0x3F, // 56 => W
  0x63, 0x14, 0x08, 0x14, 0x63, // 57 => X
  0x07, 0x08, 0x70, 0x08, 0x07, // 58 => Y
  0x61, 0x51, 0x49, 0x45, 0x43, // 59 => Z
  0x00, 0x7F, 0x41, 0x41, 0x00, // 60 => [
  0x55, 0xAA, 0x55, 0xAA, 0x55, // 61 => Backslash (Checker pattern)
  0x00, 0x41, 0x41, 0x7F, 0x00, // 62 => ]
  0x04, 0x02, 0x01, 0x02, 0x04, // 63 => ^
  0x40, 0x40, 0x40, 0x40, 0x40, // 64 => _
  0x00, 0x03, 0x05, 0x00, 0x00, // 65 => `
  0x20, 0x54, 0x54, 0x54, 0x78, // 66 => a
  0x7F, 0x48, 0x44, 0x44, 0x38, // 67 => b
  0x38, 0x44, 0x44, 0x44, 0x20, // 68 => c
  0x38, 0x44, 0x44, 0x48, 0x7F, // 69 => d
  0x38, 0x54, 0x54, 0x54, 0x18, // 70 => e
  0x08, 0x7E, 0x09, 0x01, 0x02, // 71 => f
  0x18, 0xA4, 0xA4, 0xA4, 0x7C, // 72 => g
  0x7F, 0x08, 0x04, 0x04, 0x78, // 73 => h
  0x00, 0x44, 0x7D, 0x40, 0x00, // 74 => i
  0x40, 0x80, 0x84, 0x7D, 0x00, // 75 => j
  0x7F, 0x10, 0x28, 0x44, 0x00, // 76 => k
  0x00, 0x41, 0x7F, 0x40, 0x00, // 77 => l
  0x7C, 0x04, 0x18, 0x04, 0x78, // 78 => m
  0x7C, 0x08, 0x04, 0x04, 0x78, // 79 => n
  0x38, 0x44, 0x44, 0x44, 0x38, // 80 => o
  0xFC, 0x24, 0x24, 0x24, 0x18, // 81 => p
  0x18, 0x24, 0x24, 0x18, 0xFC, // 82 => q
  0x7C, 0x08, 0x04, 0x04, 0x08, // 83 => r
  0x48, 0x54, 0x54, 0x54, 0x20, // 84 => s
  0x04, 0x3F, 0x44, 0x40, 0x20, // 85 => t
  0x3C, 0x40, 0x40, 0x20, 0x7C, // 86 => u
  0x1C, 0x20, 0x40, 0x20, 0x1C, // 87 => v
  0x3C, 0x40, 0x30, 0x40, 0x3C, // 88 => w
  0x44, 0x28, 0x10, 0x28, 0x44, // 89 => x
  0x1C, 0xA0, 0xA0, 0xA0, 0x7C, // 90 => y
  0x44, 0x64, 0x54, 0x4C, 0x44, // 91 => z
  0x00, 0x10, 0x7C, 0x82, 0x00, // 92 => {
  0x00, 0x00, 0xFF, 0x00, 0x00, // 93 => |
  0x00, 0x82, 0x7C, 0x10, 0x00, // 94 => }
};

// OLED initialisation sequence
__code uint8_t OLED_INIT_CMD[] = {
  OLED_MULTIPLEX,   0x3F,                 // set multiplex ratio  
  OLED_CHARGEPUMP,  0x14,                 // set DC-DC enable  
  OLED_MEMORYMODE,  0x02,                 // set page addressing mode
  OLED_COMPINS,     0x12,                 // set com pins
  OLED_XFLIP, OLED_YFLIP,                 // flip screen
  OLED_DISPLAY_ON                         // display on
};

// OLED global variables
__xdata uint8_t line, column, scroll;

// OLED set cursor to line start
void OLED_setline(uint8_t line) {
  I2C_start(OLED_ADDR);                   // start transmission to OLED
  I2C_write(OLED_CMD_MODE);               // set command mode
  I2C_write(OLED_PAGE + line);            // set line
  I2C_write(0x00); I2C_write(0x10);       // set column to "0"
  I2C_stop();                             // stop transmission
}

// OLED clear line
void OLED_clearline(uint8_t line) {
  OLED_setline(line);                     // set cursor to line start
  I2C_start(OLED_ADDR);                   // start transmission to OLED
  I2C_write(OLED_DAT_MODE);               // set data mode
  for(uint8_t i=128; i; i--) I2C_write(0x00);     // clear the line
  I2C_stop();                             // stop transmission
}

// OLED clear screen
void OLED_clear(void) {
  for(uint8_t i=0; i<8; i++) OLED_clearline(i);
  line = scroll;
  column = 0;
  OLED_setline((line + scroll) & 0x07);
}

// OLED clear the top line, then scroll the display up by one line
void OLED_scrollDisplay(void) {
  OLED_clearline(scroll);                 // clear line
  scroll = (scroll + 1) & 0x07;           // set next line
  I2C_start(OLED_ADDR);                   // start transmission to OLED
  I2C_write(OLED_CMD_MODE);               // set command mode
  I2C_write(OLED_OFFSET);                 // set display offset:
  I2C_write(scroll << 3);                 // scroll up
  I2C_stop();                             // stop transmission
}

// OLED init function
void OLED_init(void) {
  I2C_init();                             // initialize I2C first
  I2C_start(OLED_ADDR);                   // start transmission to OLED
  I2C_write(OLED_CMD_MODE);               // set command mode
  for(uint8_t i = 0; i < sizeof(OLED_INIT_CMD); i++)
    I2C_write(OLED_INIT_CMD[i]);          // send the command bytes
  I2C_stop();                             // stop transmission
  scroll = 0;                             // start with zero scroll
  OLED_clear();                           // clear screen
}

// OLED plot a single character
void OLED_plotChar(char c) {
  uint16_t ptr = c - 32;                  // character pointer
  ptr += ptr << 2;                        // -> ptr = (ch - 32) * 5;
  I2C_start(OLED_ADDR);                   // start transmission to OLED
  I2C_write(OLED_DAT_MODE);               // set data mode
  for(uint8_t i = 5; i; i--) I2C_write(OLED_FONT[ptr++]);
  I2C_write(0x00);                        // write space between characters
  I2C_stop();                             // stop transmission
}

// OLED write a character or handle control characters
void OLED_write(char c) {
  c = c & 0x7F;                           // ignore top bit
  // normal character
  if(c >= 32) {
    OLED_plotChar(c);
    if(++column > 20) {
      column = 0;
      if(line == 7) OLED_scrollDisplay();
      else line++;
      OLED_setline((line + scroll) & 0x07);
    }
  }
  // new line
  else if(c == '\n') {
    column = 0;
    if(line == 7) OLED_scrollDisplay();
    else line++;
    OLED_setline((line + scroll) & 0x07);
  }
  // carriage return
  else if(c == '\r') {
    column = 0;
    OLED_setline((line + scroll) & 0x07);
  }
}

// OLED print string
void OLED_print(char* str) {
  while(*str) OLED_write(*str++);
}

void main(void) {
    init();

    OLED_init();
    OLED_print("* CH552 with OLED   *");
    OLED_print("---------------------");
    OLED_print("Nicola Strappaazzon\n");
    OLED_print("!@#$%^&*()_-+=<>,.?/\n");
    OLED_print("\n");

    while(1) {}
}
