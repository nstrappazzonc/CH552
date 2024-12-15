# Flash

Para instalar la herramienta `chflasher` siga las siguientes instrucciones:

```bash
git submodule update --init
python3 -m pip install --user pyusb pyserial
```

En Linux debera otorgar permisos especiales:

```
/etc/udev/rules.d/99-ch55x.rules
SUBSYSTEM=="usb", ATTR{idVendor}=="4348", ATTR{idProduct}=="55e0", MODE="666"
sudo service udev restart
```

Una ves sincronizado el submodulo de git podra acceder al directorio y ejecutar el script de python:

```bash
cd tools/chflasher/
```

Para borrar la memoria del MCU ejecute el siguiente comando:

```bash
./chflasher.py -e
```

Obtendra la siguiente salida:

```
Found CH552
Flash size: 16 blocks, 16384 bytes.
Reserved for application: 14 blocks, 14336 bytes.
Bootloader version: 2.50
Flash Erased
```

Para subir el firmware al MCU ejecute el siguiente comando:

```bash
./chflasher.py -w -f ../../src/fade/fade.bin
```

Obtendra la siguiente salida:

```
Found CH552
Flash size: 16 blocks, 16384 bytes.
Reserved for application: 14 blocks, 14336 bytes.
Bootloader version: 2.50
Flash Erased
Filesize: 305 bytes
[====================] 100% Writing success
[====================] 100% Verify success
```
