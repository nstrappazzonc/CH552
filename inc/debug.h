
/* Debug */
/* Provide printf subroutine and delay function */

#pragma once

#include <stdint.h>

#ifndef  UART0_BAUD
#define  UART0_BAUD    9600
#endif

#ifndef UART1_BAUD
#define  UART1_BAUD    9600
#endif

void	CfgFsys( );                       // CH554 clock selection and configuration

void mDelayuS (uint16_t n); // Delay in units of uS
void mDelaymS (uint16_t n); // Delay in mS

/*******************************************************************************
* Function Name  : CH554UART0Alter()
* Description    : CH554 serial port 0 pin mapping, serial port mapping to P0.2 and P0.3

*******************************************************************************/
inline void CH554UART0Alter()
{
    PIN_FUNC |= bUART0_PIN_X;           //串口映射到P1.2和P1.3
}



/*******************************************************************************
* Function Name  : CH554UART0RcvByte()
* Description    : CH554UART0 receives a byte
* Return         : SBUF
*******************************************************************************/
inline uint8_t  CH554UART0RcvByte( )
{
    while(RI == 0);                     // wait for uart rx interrupt flag
    RI = 0;
    return SBUF;
}

/*******************************************************************************
* Function Name  : CH554UART0SendByte(uint8_t SendDat)
* Description    : CH554UART0 sends a byte
* Input          : uint8_t SendDat; the data to be sent
*******************************************************************************/
inline void CH554UART0SendByte(uint8_t SendDat)
{

        SBUF = SendDat;
        while(TI ==0);                  // wait for transmit to finish (TI == 1)
        TI = 0;
}

/*******************************************************************************
* Function Name  : CH554UART1Alter()
* Description    : Set the alternate pin mappings for UART1 (TX on P3.2, RX on P3.4)
*******************************************************************************/
inline void CH554UART1Alter()
{
    PIN_FUNC |= bUART1_PIN_X;
}

/*******************************************************************************
* Function Name  : UART1Setup()
* Description    : CH554串口1初始化
*******************************************************************************/
inline void	UART1Setup()
{
    U1SM0 = 0;                          //UART1选择8位数据位
    U1SMOD = 1;                         //快速模式
    U1REN = 1;                          //使能接收
    // should correct for rounding in SBAUD1 calculation 
    SBAUD1 = 256 - FREQ_SYS/16/UART1_BAUD;
}

/*******************************************************************************
* Function Name  : CH554UART1RcvByte()
* Description    : CH554UART1接收一个字节
* Return         : SBUF
*******************************************************************************/
inline uint8_t  CH554UART1RcvByte( )
{
    while(U1RI == 0);                   //查询接收，中断方式可不用
    U1RI = 0;
    return SBUF1;
}

/*******************************************************************************
* Function Name  : CH554UART1SendByte(uint8_t SendDat)
* Description    : CH554UART1发送一个字节
* Input          : uint8_t SendDat；要发送的数据
*******************************************************************************/
inline void CH554UART1SendByte(uint8_t SendDat)
{
        SBUF1 = SendDat;                //查询发送，中断方式可不用下面2条语句,但发送前需TI=0
        while(U1TI ==0);
        U1TI = 0;
}

#if SDCC < 370
void putchar(char c);
char getchar();
#else
int putchar(int c);
int getchar(void);
#endif

/*******************************************************************************
* Function Name  : CH554WDTModeSelect(uint8_t mode)
* Description    : CH554 watchdog mode selection
* Input          : uint8_t mode
                   0  timer
                   1  watchDog
* Output         : None
* Return         : None
*******************************************************************************/
inline void CH554WDTModeSelect(uint8_t mode)
{
   SAFE_MOD = 0x55;
   SAFE_MOD = 0xaa;                                                             //Enter Safe Mode
   if(mode){
     GLOBAL_CFG |= bWDOG_EN;                                                    //Start watchdog reset
   }

   else GLOBAL_CFG &= ~bWDOG_EN;	                                            //Start watchdog only as a timer
   SAFE_MOD = 0x00;                                                             //exit safe Mode
   WDOG_COUNT = 0;                                                              //Watchdog assignment initial value

}

/*******************************************************************************
* Function Name  : CH554WDTFeed(uint8_t tim)
* Description    : CH554 watchdog timer time setting
* Input          : uint8_t tim watchdog reset time setting

                   00H(6MHz)=2.8s
                   80H(6MHz)=1.4s
* Output         : None
* Return         : None
*******************************************************************************/
inline void CH554WDTFeed(uint8_t tim)
{

   WDOG_COUNT = tim;                                                            // Watchdog counter assignment

}
