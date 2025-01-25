# DHT11 - Sensor de temperatura y humedad

Este sensor opera entre 3.3V y 5.5V, usa un protocolo de comunicación propietario del tipo "single wire", y su precisión oscila entre +/- 5 % en humedad, y +/- 2C en temperatura.

![](https://github.com/nstrappazzonc/CH552/blob/main/assets/src/dht11/protoboard.jpeg)

La conexión entre el sensor y el MCU es muy simple, puedes escoger cualquier pin disponible, en este caso se usó el P3.2:

![](https://github.com/nstrappazzonc/CH552/blob/main/assets/src/dht11/schematic.png)

## Single wire protocol

![](https://github.com/nstrappazzonc/CH552/blob/main/assets/doc/pulseview/dht11_02.png)

**NOTA:** Para que la comunicación con el sensor funcione, el reloj debe estar bien configurado, asegúrate de validarlo con un osciloscopio o un [analizador lógico](https://github.com/nstrappazzonc/CH552/blob/main/doc/logic_analyze.md).

[Datasheet](https://github.com/nstrappazzonc/CH552/blob/main/doc/datasheets/DHT11.pdf)
