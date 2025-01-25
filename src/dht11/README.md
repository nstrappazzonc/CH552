# DHT11 - Sensor de temperatura y humedad

[Datasheet](https://github.com/nstrappazzonc/CH552/blob/main/doc/datasheets/DHT11.pdf)

Este sensor opera entre 3.3V y 5.5V, usa un protocolo de comunicación propietario del tipo "single wire", y su precisión oscila entre +/- 5 % en humedad, y +/- 2C en temperatura.

![](https://github.com/nstrappazzonc/CH552/blob/main/assets/src/dht11/protoboard.jpeg)

La conexión entre el sensor y el MCU es muy simple, puedes escoger cualquier pin disponible, en este caso se usó el P3.2:

![](https://github.com/nstrappazzonc/CH552/blob/main/assets/src/dht11/schematic.png)

## Single wire protocol

El DHT11 usa un solo cable para comunicarse, comenzando con una señal de inicio del microcontrolador: el pin se pone en nivel bajo por al menos 18 ms y luego se libera (nivel alto). El sensor responde con un pulso bajo de 80 µs seguido de un pulso alto de 80 µs para indicar que está listo. A continuación, el DHT11 envía 40 bits de datos (5 bytes), los dos primeros bytes representan la humedad entera y decimal, luego los siguientes dos bytes representan la temperatura entera y decimal, por último un byte que es un checksum para validar los datos.

![](https://github.com/nstrappazzonc/CH552/blob/main/assets/doc/pulseview/dht11_02.png)

**NOTA:** Para que la comunicación con el sensor funcione, el reloj debe estar bien configurado, asegúrate de validarlo con un osciloscopio o un [analizador lógico](https://github.com/nstrappazzonc/CH552/blob/main/doc/logic_analyze.md).
