#include <stdint.h>

uint8_t EEPROM_read(uint8_t addr);                // Read single byte from data flash.
void EEPROM_write(uint8_t addr, uint8_t value);   // Write single byte to data flash.
void EEPROM_update(uint8_t addr, uint8_t value);  // Write if changed (reduces write cycles).
