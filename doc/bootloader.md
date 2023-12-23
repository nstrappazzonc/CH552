# Bootloader

El CI viene con un cargador de arranque (Bootloader) pre-cargado de fabrica, por lo que escribir el firmware (programa) es muy fácil usando el puerto USB.

Sino hay ningún programa grabado, automaticamente entra en el modo bootloader.

Para entrar en este modo, debe desconectar el cable USB, dejar presionado el pulsador de bootmode y conectar el cable USB y una vez conectado puede soltar el pulsador. 

Una vez en modo bootloader, podrá verificar su estado listando los dispositivos USB conectados de la siguiente forma:

```
lsusb
```

Si todo esta bien, deberá ver un PID y VID correspondiente a este `4348:55e0`. El nombre del device es WinChipHead BRCM20702 Hub

Sino hay un prograna entra en el bootloader, al cabo de unos segundos sino se hace uso del bootloader, se inicia el programa en caso de que exista.

Una vez que este en el modo bootloader, inmediatamente suba el programa con el siguiente comando.

```
make flash
```

Importante, sino sube el programa en los proximos 15 segundos, sale del modo bootloader y se inicia el último programa en memoria.
