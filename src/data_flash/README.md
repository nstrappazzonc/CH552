# DataFlash

The [CH552G](https://www.wch-ic.com/products/CH552.html) has 128 bytes of DataFlash allocated from F000H to F3FFH. This type of Flash memory is used for data storage in a manner similar to EEPROM. Unlike program Flash, DataFlash is specifically optimized for frequent data storage and writing. This makes it suitable for storing small amounts of persistent data, such as configurations or critical parameters that need to be preserved after a reset or power-off.

To demonstrate how DataFlash is used, a base example [Button & LED RGB](https://github.com/nstrappazzonc/CH552/tree/main/src/button_led_rgb) was modified to save the last color state. If the MCU is reset or disconnected, it will retain the last state.
