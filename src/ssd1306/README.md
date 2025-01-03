# SSD1306

En este ejemplo hacemos uso de una pantalla [monocromática OLED de 0,96](https://es.aliexpress.com/item/1005005941908229.html) pulgadas que corresponde a una resolución 128x64 píxel, funciona con 3v y 5v, usa una interfaz de comunicación I2C, el controlador de la pantalla es SSD1315 y el código fuente es compatible con sus versiones antiguas como el SSD1306 y SSD1309.

![](https://github.com/nstrappazzonc/CH552/blob/main/assets/src/ssd1306/protoboard.jpeg)

La conexión del microcontrolador con la pantalla OLED es muy simple por la interfaz I2C, recuerde que el microcontrolador CH552 no tiene registros dedicados para I2C y se hace emulando, por lo que puede realizar la conexión en cualquier pin disponible.

![](https://github.com/nstrappazzonc/CH552/blob/main/assets/src/ssd1306/schematic.png)

El diagrama esquemático mostrado anteriormente es una representación simple que pretende mostrar la conexión de la pantalla OLED al MCU, el circuito necesario para que funcione el MCU es ignorado intencionalmente.

Hay una técnica del `screen_buffer` que se utiliza para dibujar en la pantalla, si nuestra pantalla es de 128x64 píxel, al definir la variable `screen_buffer` ocupará 128x64=8192 bytes, lamentablemente el CH552 tiene una RAM de 256 bytes por lo que no podemos utilizar dicha técnica.
