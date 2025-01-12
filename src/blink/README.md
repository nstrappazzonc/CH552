# Blink

This is a simple blink example (turning on and off with an intermediate pause), also known as a flip-flop, which uses the P3.0 port to send a voltage of 5V and 0V.

![](https://github.com/nstrappazzonc/CH552/blob/main/assets/src/blink/schematic.png?raw=true)

In the source code, we show two ways to achieve the same result:

## Option 1

```c
delay(1000);
LED = 0;
delay(1000);
LED = 1;
```

## Option 2

```c
delay(1000);
LED =! LED;
```
