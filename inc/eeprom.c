#include <stdint.h>
#include "eeprom.h"
#include <ch552.h>

uint8_t WriteDataFlash(uint8_t addr, unsigned char *buf, uint8_t len)
{
    uint8_t i;
    SAFE_MOD = 0x55;
    SAFE_MOD = 0xAA;                                                           //进入安全模式
    GLOBAL_CFG |= bDATA_WE;                                                    //使能DataFlash写
    SAFE_MOD = 0;                                                              //退出安全模式 
    ROM_ADDR_H = DATA_FLASH_ADDR >> 8;
    addr <<= 1;
    for(i=0;i<len;i++)
    {
      ROM_ADDR_L = addr + i*2;
      ROM_DATA_L = *(buf+i);      
      if ( ROM_STATUS & bROM_ADDR_OK ) {                                     // 操作地址有效
        ROM_CTRL = ROM_CMD_WRITE;                                           // 写入
      }
      if((ROM_STATUS ^ bROM_ADDR_OK) > 0) return i;                          // 返回状态,0x00=success,  0x02=unknown command(bROM_CMD_ERR)
    }
    SAFE_MOD = 0x55;
    SAFE_MOD = 0xAA;                                                           //进入安全模式
    GLOBAL_CFG &= ~bDATA_WE;                                                   //开启DataFlash写保护
    SAFE_MOD = 0;                                                              //退出安全模式 
    return i;   
}

uint8_t ReadDataFlash(uint8_t addr, uint8_t len, unsigned char *buf)
{
    uint8_t i;
    ROM_ADDR_H = DATA_FLASH_ADDR >> 8;
    addr <<= 1;
    for(i=0;i<len;i++){
      ROM_ADDR_L = addr + i*2;                                                   //Addr必须为偶地址
      ROM_CTRL = ROM_CMD_READ;
      *(buf+i) = ROM_DATA_L;
    }
    return i;
}
