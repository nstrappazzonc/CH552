#include <ch552.h>
#include <gpio.h>
#include <utils.h>
#include <ssd1306.h>
#include <stdio.h>

#define DHT11 P32

int I_RH, D_RH, I_Temp, D_Temp, CheckSum; 

#define _nop_() __asm nop __endasm

void delay_us2(uint16_t us) {
    while (us--) {
        _nop_();
    }
}

void delay_ms(uint16_t ms) {
    while (ms--) {
        delay_us2(1000);
    }
}

uint8_t request(void) {
    PIN_low(DHT11);
    delay_ms(18);
    PIN_high(DHT11);
    // delay_ms(20);

    // if (DHT11) return 10;  // Error si el pin no baja
    // while (!DHT11);
    // while (DHT11 == 1);

    while(DHT11==1);
    while(DHT11==0);
    while(DHT11==1);

    return 0;
}

uint8_t DHT11_read_byte(void) {
    uint8_t byte = 0;
    for(uint8_t i = 0; i < 8; i++) {
        while(DHT11==0);  // Espera a que el pin suba a nivel alto

        delay_us2(30);  // Espera para determinar si es un 0 o un 1
        if (DHT11==1) {
            byte |= (1 << (7 - i));  // Si el pin sigue en alto, es un 1
            // byte = (byte<<1)|(0x01);
        } else {
            // byte = (byte<<1);
        }

        while(DHT11 == 1);  // Espera a que el pin vuelva a nivel bajo
    }
    return byte;
}

// void response() {
//     // delay(40);
//     // PIN_read(DHT11);
//     // PIN_read(DHT11);
//     // PIN_read(DHT11);

//     while(PIN_read(DHT11) == 1);
//     while(PIN_read(DHT11) == 0);
//     while(PIN_read(DHT11) == 1);
// }

// int receive_data() {
//     int q,c=0;  
//     for (q=0; q<8; q++) {
//         while(PIN_read(DHT11) == 0);

//         delay(30);

//         if(PIN_read(DHT11) == 1)
//             // c <<= 1;
//             c = (c<<1)|(0x01);
//         else
//             // c |= 1;
//             c = (c<<1);

//         while(PIN_read(DHT11) == 1);
//     }
//     return c;
// }

void main(void) {
    unsigned char dat[20];

    init();
    oled_init();

    PIN_high(DHT11);
    delay(1000);

    while(1) {
        uint8_t data[5] = {0};


        oled_cursor(0,0);
        oled_print("Ok1");
        delay(1000);
        uint8_t a = request();
        // response();
        sprintf(dat, "Ok2 %d", a);
        oled_cursor(0,0);
        oled_print(dat);

        for (uint8_t i = 0; i < 5; i++) {
            data[i] = DHT11_read_byte();
        }

        // I_RH    = receive_data(); // store first eight bit in I_RH.
        // D_RH    = receive_data(); // store next eight bit in D_RH.
        // I_Temp  = receive_data(); // store next eight bit in I_Temp.
        // D_Temp  = receive_data(); // store next eight bit in D_Temp.
        // CheckSum= receive_data(); // store next eight bit in CheckSum.

        // if ((I_RH + D_RH + I_Temp + D_Temp) != CheckSum) {
        //     oled_cursor(0,0);
        //     oled_print("Read DHT11 Error");
        // }

        sprintf(dat, "H: %d", data[0]);
        oled_cursor(0,1);
        oled_print(dat);
        // sprintf(dat, "T: %d.%dC", I_Temp, D_Temp);
        // oled_cursor(0,1);
        // oled_print(dat);

        delay(1000);
    }
}
