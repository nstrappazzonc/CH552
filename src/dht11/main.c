#include <ch552.h>
#include <utils.h>
#include <ssd1306.h>
#include <stdio.h>

SBIT(P32, 0xB0, 2);
SBIT(P14, 0x90, 4);

#define DHT11 P32
#define DEBUG1 P14

uint8_t IH, DH, IT, DT, CS;

void DHT11_SetOutput() {
    P3_MOD_OC &= ~(1 << 2);  // Configura P3.0 como push-pull
    P3_DIR_PU |= (1 << 2);   // Configura P3.0 como salida
}

void DHT11_SetInput() {
    P3_MOD_OC |= (1 << 2);   // Configura P3.0 como open-drain
    P3_DIR_PU &= ~(1 << 2);  // Configura P3.0 como entrada
}

uint8_t DHT11_ReadByte(void) {
    uint8_t data = 0;

    for (uint8_t i = 0; i < 8; i++) {
        unsigned int timeout = 10000;
        DEBUG1 = 1;
        while (DHT11 == 0);
        DEBUG1 = 0;
        delay_us(30);
        if (DHT11 == 1) {
            data |= (1 << (7 - i));
            while (DHT11 == 1 && --timeout);
        }
    }

    return data;
}

void main(void) {
    unsigned char dat[20];
    uint8_t counter = 0;

    init();
    delay_ms(1000);
    oled_init();
    oled_cursor(0,0);
    oled_print("DHT11");

    P1_MOD_OC &= ~(1 << 4);
    P1_DIR_PU |= (1 << 4);

    while(1) {
        // EA = 0;
        DHT11_SetOutput();
        DHT11 = 0;
        delay_ms(18);
        DHT11 = 1;

        DHT11_SetInput();
        while(DHT11 == 1);
        while(DHT11 == 0);
        while(DHT11 == 1);

        IH = DHT11_ReadByte();
        DH = DHT11_ReadByte();
        IT = DHT11_ReadByte();
        DT = DHT11_ReadByte();
        CS = DHT11_ReadByte();

        // EA = 1;
    
        if ((IH + DH + IT + DT) != CS) {
            oled_cursor(0,4);
            oled_print("-> Sensor Error.");
        }

        sprintf(dat, "T: %d.%d", IT, DT);
        oled_cursor(0,5);
        oled_print(dat);
        sprintf(dat, "H: %d.%d", IH, DH);
        oled_cursor(0,6);
        oled_print(dat);
        sprintf(dat, "L: %d", counter++);
        oled_cursor(0,7);
        oled_print(dat);

        delay_ms(1000);
    }
}
