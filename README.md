# CH552G

Este es un facinante y bien dotado MCU de 8-bit de muy bajo coste, diseñado y fabricado en china por [Jiangsu Heng Qin Ltd. (WCH)](http://www.wch-ic.com). De momento nos vamos a centrar en el [CH552G](https://www.wch-ic.com/products/CH552.html) que está basado en la arquitectura 8051 [CISC](https://en.wikipedia.org/wiki/Complex_instruction_set_computer) y su núcleo es especificamente E8051, lo más atractivo de este MCU es su puerto USB y un oscilador interno de 24Mhz entre otras cosas.

![](https://github.com/nstrappazzonc/CH552/blob/main/img/system_block_diagram.png?raw=true)

El 8051 pertenece a una familia MCS-51, y es tan popular que se ha hecho abierto para que cualquiera pueda conocerlo y/o replicarlo, en [OpenCores](https://opencores.org/projects/8051) puedes ver los diseños del MCU.

## Especificaciones

Estas son las especificaciones más relevantes del MCU, para más detalles vea la [documentación oficial](https://www.wch-ic.com/products/CH552.html).

- Trabaja entre 5V y 3.3v.
- Incorpora 16KB Code Flash, 1KB XRAM, 256B iRAM, 128B DataFlash.
- Soporta los protocolos de comunicación USB 2.0, UART, SPI, ISP.
- Tiene 3 timer, 2 signal capture, 2 PWM, y 4 ADC.
- Incorpora BootLoader.
- Incorpora un reloj interno de 24MHz.
- Incorpora un identificador numerico único.
- Encapsulados disponibles: TSSOP-20, SOP-16, MSOP-10.

**IMPORTANTE:** Se debe destacar que hay una limitación con la ROM o el Code Flash es un proceso iFlash™, el cual puede ser programado unas 200 veces. No es tan malo, pero debe tenerlo en cuenta.

## Esquema minimo

![](https://github.com/nstrappazzonc/CH552/blob/main/img/minimal_schematic.jpg?raw=true)

En el protoboard nos queda de la siguiente forma:

![](https://github.com/nstrappazzonc/CH552/blob/main/img/minimal_protoboard.jpg?raw=true)
