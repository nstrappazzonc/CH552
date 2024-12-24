#include <stdint.h>

uint8_t WriteDataFlash(uint8_t addr, unsigned char *buf, uint8_t len);
uint8_t ReadDataFlash(uint8_t addr, uint8_t len, unsigned char *buf);
