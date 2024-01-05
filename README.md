# CH552

Este es un facinante, repotenciado y bien dotado MCU de 8-bit de muy bajo coste, diseñado y fabricado en china por [Jiangsu Heng Qin Ltd. (WCH)](http://www.wch-ic.com). De momento nos vamos a centrar en el [CH552G](https://www.wch-ic.com/products/CH552.html) que está basado en la arquitectura 8051 [CISC](https://en.wikipedia.org/wiki/Complex_instruction_set_computer) y su núcleo es especificamente E8051, lo más atractivo de este MCU es su puerto USB y un oscilador interno de 24Mhz entre otras cosas. Para programarlo nos debemos basar bastante en el C51. Existen diferentes empaquetados y versiones del MCU cómo; CH551, CH552, CH554 y CH559.

Puedes conseguir los MCU en la tienda oficial de [AliExpress](https://wchofficialstore.es.aliexpress.com/store/1100367542) o en [JLCMC](https://jlcmc.com).

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

![](https://github.com/nstrappazzonc/CH552/blob/main/img/pinout2.png?raw=true)

El pinout que mostramos es básico para hacerse una idea, hay más funcionalidades en los puertos. Revisar el [datasheet](https://github.com/nstrappazzonc/CH552/blob/main/doc/CH552.pdf?raw=true) para mayor detalle.

**IMPORTANTE:** Se debe destacar que hay una limitación con la ROM o el Code Flash es un proceso iFlash™, el cual puede ser programado unas 200 veces. No es tan malo, pero debe tenerlo en cuenta.

## Componentes

Use los siguientes componentes para construir el circuito mínimo:

- Un IC CH552G.
- Condensador de 100nF x2.
- Resistencia de 10K x2.
- Resistencia de 1K x2.
- Dos pulsadores. Uno para el boot y otro para el reset.

## Esquema mínimo

![](https://github.com/nstrappazzonc/CH552/blob/main/img/minimal_schematic.jpg?raw=true)

En el protoboard nos queda de la siguiente forma:

![](https://github.com/nstrappazzonc/CH552/blob/main/img/minimal_protoboard.jpg?raw=true)

## Códigos fuentes

En este repositorio tiene una colección de códigos fuentes de ejemplos escrito en C para empezar. Todos los códigos fuentes han sido previamente verificados para garantizar su correcto funcionamiento.

- [blink](https://github.com/nstrappazzonc/CH552/tree/main/src/blink) Usa un puerto de salida para encender y apaga un LED.
- [button](https://github.com/nstrappazzonc/CH552/tree/main/src/button) Usa un puerto de una entrada para un pulsador y otro puerto de salida para el LED.
- [fade](https://github.com/nstrappazzonc/CH552/tree/main/src/fade) Hace uso del PWM para endencer y apagar un LED con atenuación.
- [cdc](https://github.com/nstrappazzonc/CH552/tree/main/src/cdc) Envia y recibe mensajes por el protocolo UART.
- [adc](https://github.com/nstrappazzonc/CH552/tree/main/src/adc) Captura la variación de voltaje por un puerto de entrada.
- [USB/cdc](https://github.com/nstrappazzonc/CH552/tree/main/src/usb/cdc/tx) Envia mensajes a través del puerto USB.
