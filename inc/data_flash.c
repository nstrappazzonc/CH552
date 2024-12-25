#include <stdint.h>
#include "data_flash.h"
#include <ch552.h>

uint8_t WriteDataFlash(uint8_t addr, unsigned char *buf, uint8_t len)
{
  uint8_t i;
  SAFE_MOD = 0x55;
  SAFE_MOD = 0xAA;                                 //Enter safe mode.
  GLOBAL_CFG |= bDATA_WE;                          //Enable DataFlash writing.
  SAFE_MOD = 0;                                    //Exit safe mode.
  ROM_ADDR_H = DATA_FLASH_ADDR >> 8;
  addr <<= 1;
  for(i=0;i<len;i++)
  {
    ROM_ADDR_L = addr + i*2;
    ROM_DATA_L = *(buf+i);      
    if ( ROM_STATUS & bROM_ADDR_OK ) {             // The operation address is valid.
      ROM_CTRL = ROM_CMD_WRITE;                    // Write
    }
    if((ROM_STATUS ^ bROM_ADDR_OK) > 0) return i;  // Return status, 0x00 = success, 0x02 = unknown command (bROM_CMD_ERR)
  }
  SAFE_MOD = 0x55;
  SAFE_MOD = 0xAA;                                 //Enter safe mode.
  GLOBAL_CFG &= ~bDATA_WE;                         //Enable DataFlash write protection
  SAFE_MOD = 0;                                    //exit safe mode
  return i;   
}

uint8_t ReadDataFlash(uint8_t addr, uint8_t len, unsigned char *buf)
{
  uint8_t i;
  ROM_ADDR_H = DATA_FLASH_ADDR >> 8;
  addr <<= 1;
  for(i=0;i<len;i++){
    ROM_ADDR_L = addr + i*2; //Addr must be an even address
    ROM_CTRL = ROM_CMD_READ;
    *(buf+i) = ROM_DATA_L;
  }
  return i;
}
