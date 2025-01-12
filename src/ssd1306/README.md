# SSD1306

In this example, we use a [0.96-inch monochrome OLED](https://es.aliexpress.com/item/1005005941908229.html) screen with a 128x64 pixel resolution, which operates on 3V and 5V. It uses an I2C communication interface, and the screen controller is SSD1315. The source code is also compatible with older versions, such as SSD1306 and SSD1309.

![](https://github.com/nstrappazzonc/CH552/blob/main/assets/src/ssd1306/protoboard.jpeg)

The connection between the microcontroller and the OLED screen is very simple due to the I2C interface. Keep in mind that the CH552 microcontroller does not have dedicated I2C registers and emulates it, so you can make the connection to any available pin.

![](https://github.com/nstrappazzonc/CH552/blob/main/assets/src/ssd1306/schematic.png)

The schematic diagram shown above is a simple representation intended to show the connection between the OLED screen and the MCU. The circuit necessary for the MCU to function is intentionally omitted.

A technique called `screen_buffer` is used to draw on the screen. If our screen is 128x64 pixels, defining the `screen_buffer` variable will occupy 128x64 = 8192 bytes. Unfortunately, the CH552 has only 256 bytes of RAM, so we cannot use this technique.
