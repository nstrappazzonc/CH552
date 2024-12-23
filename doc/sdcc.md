# SDCC (Small Devices C Compiler)

Es un compilador libre para el lenguaje Embedded-C que permite desarrollar en microcontroladores de 8-bit. [Sitio oficial](https://sdcc.sourceforge.net)

## Instalación:

### Linux

```
sudo apt-install build-essential sdcc
```

### MAC OS X

```
brew install sdcc
brew install binutils
```

Agregar las siguientes líneas al fichero `.bash_profile`:

```
export PATH="/opt/homebrew/opt/binutils/bin:$PATH"
export LDFLAGS="-L/opt/homebrew/opt/binutils/lib"
export CPPFLAGS="-I/opt/homebrew/opt/binutils/include"
```

#### Troubleshooting

Si al compular tienes el siguiente error, es que te falto hacer el `export` de las variables anteriores.

```
objcopy -I ihex -O binary blink.ihx blink.bin
make: objcopy: No such file or directory
make: *** [blink.bin] Error 1
```

## Compiler

```
sdcc -c -V -mmcs51 --model-small -I ../../inc/ --xram-size 0x0400 --xram-loc 0x0000 -DFREQ_SYS=24000000 main.c -o main.ihx
```
