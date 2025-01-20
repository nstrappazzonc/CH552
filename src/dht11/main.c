#include <ch552.h>
#include <utils.h>
#include <ssd1306.h>
#include <stdio.h>

SBIT(P32, 0xB0, 2);

#define DHT11 P32

uint8_t I_H, D_H, I_T, D_T, CheckSum;

// sbit DHT11 = P3^0;  // Define el pin conectado al DHT11

void DHT11_SetOutput() {
    P3_MOD_OC &= ~(1 << 2);  // Configura P3.0 como push-pull
    P3_DIR_PU |= (1 << 2);   // Configura P3.0 como salida
}

void DHT11_SetInput() {
    P3_MOD_OC |= (1 << 2);   // Configura P3.0 como open-drain
    P3_DIR_PU &= ~(1 << 2);  // Configura P3.0 como entrada
}

uint8_t DHT11_CheckResponse() {
    unsigned int timeout = 100; // Timeout para evitar bloqueos

    // Espera el pulso bajo (~80 µs)
    while (DHT11 && --timeout);
    if (timeout == 0) return 0;

    timeout = 100; // Reinicia el timeout
    // Espera el pulso alto (~80 µs)
    while (!DHT11 && --timeout);
    if (timeout == 0) return 0;

    return 1; // Respuesta válida
}

unsigned char DHT11_ReadByte() {
    unsigned char i, data = 0;

    for (i = 0; i < 8; i++) {
        unsigned int timeout = 100; // Timeout para evitar bloqueos

        // Espera el pulso bajo (~50 µs)
        while (DHT11 && --timeout);
        if (timeout == 0) return 0; // Timeout: error de sincronización

        timeout = 100; // Reinicia el timeout

        // Espera el inicio del pulso alto
        while (!DHT11 && --timeout); 
        if (timeout == 0) return 0; // Timeout: error de sincronización

        // Mide la duración del pulso alto
        delay_us(30); // Espera 30 µs para pasar a la parte central del pulso
        if (DHT11) {
            data |= (1 << (7 - i)); // Si el pulso sigue alto, es un '1'
            // Espera a que termine el pulso alto
            timeout = 100;
            while (DHT11 && --timeout);
        }
    }

    return data;
}

uint8_t receive_data(void) {
    uint8_t byte = 0;
    for (uint8_t i=0; i<8; i++) {
        uint8_t timeout = 1000;

        while(DHT11 && --timeout);
        if (timeout == 0) return 0;
        // while(!DHT11);
        timeout = 1000;
        while (!DHT11 && --timeout); 
        if (timeout == 0) return 0;

        delay_us(30);
        
        if(DHT11){
            // byte <<= 1;
            byte |= (1 << (7 - i));
            // byte = (byte<<1)|(0x01);
            timeout = 1000;
            while(DHT11 && --timeout);
        }else{
            byte |= 1;
            // byte = (byte<<1);
        }

        // while(DHT11);
    }
    return byte;
}

void main(void) {
    unsigned char dat[20];
    uint8_t counter = 0;

    init();
    delay_ms(1000);
    oled_init();
    oled_cursor(0,0);
    oled_print("DHT11");

    // Init DHT11:
    // P3_MOD_OC |= (1 << DHT11);
    // P3_DIR_PU |= (1 << DHT11);



    while(1) {
        // DHT11_Start();
        EA = 0;  // Desactiva interrupciones
        DHT11_SetOutput();
        DHT11 = 0;         // Señal de inicio
        delay_ms(18);      // Mantén bajo por 18 ms
        DHT11 = 1;
        // delay_us(30);      // Liberar la línea
        // Request:
        // DHT11 = 0;
        // delay_ms(18);
        // DHT11 = 1;
        // delay_ms(30);

        DHT11_SetInput();

        // Verify response:
        // while(!DHT11);
        // // oled_cursor(0,1);
        // // oled_print("-> Ok 1");
        // while(DHT11);
        // // oled_cursor(0,2);
        // // oled_print("-> Ok 2");
        // while(!DHT11);
        // DHT11_Start();
        // if (!DHT11_CheckResponse()) {
        //     oled_cursor(0,3);
        //     oled_print("-> Ko");
        // };

    if (!DHT11_CheckResponse()) {
        EA = 1;        // Reactiva interrupciones
            oled_cursor(0,3);
            oled_print("-> Ko");
    }

        oled_cursor(0,3);
        oled_print("-> Ok");

        I_H      = DHT11_ReadByte(); // store first eight bit in I_RH.
        D_H      = DHT11_ReadByte(); // store next eight bit in D_RH.
        I_T      = DHT11_ReadByte(); // store next eight bit in I_Temp.
        D_T      = DHT11_ReadByte(); // store next eight bit in D_Temp.
        CheckSum = DHT11_ReadByte(); // store next eight bit in CheckSum.
    
        if ((I_H + D_H + I_T + D_T) != CheckSum) { // TODO: If x == 0 is err.
            oled_cursor(0,4);
            oled_print("-> Sensor Error.");
        } else {
            oled_cursor(0,4);
            oled_print("-> Sensor Ok.");
        }

        sprintf(dat, "T: %d.%d", I_T, D_T);
        oled_cursor(0,5);
        oled_print(dat);
        sprintf(dat, "H: %d.%d", I_H, D_H);
        oled_cursor(0,6);
        oled_print(dat);

        sprintf(dat, "L: %d", counter++);
        oled_cursor(0,7);
        oled_print(dat);

        delay_ms(1000);
    }
}
