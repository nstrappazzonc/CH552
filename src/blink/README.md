# Blink

Este es un ejemplo simple de un blink (encendido y apagado con una pausa intermedia), tambien se suele llamar flip flop, que hace uso del puerto P3.0  para enviar un voltaje de 5v y 0v.

![](https://github.com/nstrappazzonc/CH552/blob/main/assets/blink/schematic.png?raw=true)

En el código fuente mostramos dos formas de hacer lo mismo:

## Opción 1

```c
delay(1000);
LED = 0;
delay(1000);
LED = 1;
```

## Opción 2

```c
delay(1000);
LED =! LED;
```
