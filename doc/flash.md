# Flash



git submodule update --init
python3 -m pip install --user pyusb pyserial


/etc/udev/rules.d/99-ch55x.rules
SUBSYSTEM=="usb", ATTR{idVendor}=="4348", ATTR{idProduct}=="55e0", MODE="666"

sudo service udev restart



```
cd tools/chflasher/
./chflasher.py -e
```

```
Found CH552
Flash size: 16 blocks, 16384 bytes.
Reserved for application: 14 blocks, 14336 bytes.
Bootloader version: 2.50
Flash Erased
```

```
./chflasher.py -w -f ../../src/fade/fade.bin
```

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
