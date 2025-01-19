#include <ch552.h>
// #include <gpio.h>
#include <utils.h>
#include <ssd1306.h>
#include <stdio.h>

// SBIT(P32, 0xB0, 2); // P3.2
SBIT(P33, 0xB0, 3); // P3.3

#define DHT11 P33

uint8_t I_H, D_H, I_T, D_T, CheckSum;

uint8_t receive_data(void) {
    uint8_t byte = 0;
    for (uint8_t i=0; i<8; i++) {
        while(!DHT11);

        mDelayuS(30);
        // byte <<= 1;
        // byte |= DHT11;
        if(DHT11){
            byte <<= 1;
        //     byte = (byte<<1)|(0x01);
        }else{
            byte |= 1;
        //     byte = (byte<<1);
        }

        while(DHT11);
    }
    return byte;
}

void main(void) {
    unsigned char dat[20];

    init();
    mDelayuS(5000);

    oled_init();
    



    // PIN_high(DHT11);

    oled_cursor(0,0);
    oled_print("DHT11");

    uint8_t counter = 0;

    while(1) {
        // PIN_high(DHT11);
        // delay(10);

        P3_MOD_OC |= (1 << DHT11);
        P3_DIR_PU |= (1 << DHT11);
        // PIN_low(DHT11);
        DHT11 = 0;
        delay(18);
        DHT11 = 1;
        // PIN_high(DHT11);

        while(!DHT11);
        // while(DHT11==1);
        oled_cursor(0,1);
        oled_print("-> Ok 1");
        while(DHT11);
        // while(DHT11==0);
        oled_cursor(0,2);
        oled_print("-> Ok 2");

        while(!DHT11);
        // while(DHT11==1);
        oled_cursor(0,3);
        oled_print("-> Ok 3");

        I_H     = receive_data(); // store first eight bit in I_RH.
        D_H     = receive_data(); // store next eight bit in D_RH.
        I_T     = receive_data(); // store next eight bit in I_Temp.
        D_T     = receive_data(); // store next eight bit in D_Temp.
        CheckSum = receive_data(); // store next eight bit in CheckSum.
        // oled_cursor(0,4);
        // oled_print("-> Ok 4");
        if ((I_H + D_H + I_T + D_T) != CheckSum) { // TODO: If x == 0 is err.
            oled_cursor(0,4);
            oled_print("-> Sensor Error.");
        } else {
            oled_cursor(0,4);
            oled_print("-> Sensor Ok.");
        }

        sprintf(dat, "T: %d.%dC", I_T, D_T);
        oled_cursor(0,5);
        oled_print(dat);

        sprintf(dat, "L: %d", counter++);
        oled_cursor(0,7);
        oled_print(dat);

        delay(1000);
    }
}
