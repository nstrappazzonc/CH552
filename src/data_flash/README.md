# DataFlash

El [CH552G](https://www.wch-ic.com/products/CH552.html) tiene 128 bytes de DataFlash asignados desde F000H hasta F3FFH, es un tipo de memoria Flash que se utiliza para el almacenamiento de datos de manera similar a una EEPROM. A diferencia de la Flash de programa, la DataFlash está optimizada específicamente para el almacenamiento y la escritura frecuente de datos. Esto la hace adecuada para almacenar pequeñas cantidades de datos persistentes, como configuraciones o parámetros críticos que necesiten mantenerse después de un reinicio o apagado.

Para demostrar mediante un ejemplo como se usa el DataFlash se usó un ejemplo base [Button & LED RGB](https://github.com/nstrappazzonc/CH552/tree/main/src/button_led_rgb) el cual se modificó para guardar el último estado del color, si se reinicia o se desconecta el MCU este conservará el último estado.
