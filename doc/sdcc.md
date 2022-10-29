# SDCC (Small Devices C Compiler)

Es un compilador libre para el lenguaje C que permite desarrollar microcontroladores de 8-bit.

Sitio oficial: [https://sdcc.sourceforge.net](https://sdcc.sourceforge.net)


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
export CPPFLAGS="-I/usr/local/opt/binutils/include"
export LDFLAGS="-L/usr/local/opt/binutils/lib"
export PATH="/usr/local/opt/binutils/bin:$PATH"
```

## Compiler

```
sdcc -c -V -mmcs51 --model-small -I ../../include/ --xram-size 0x0400 --xram-loc 0x0000 -DFREQ_SYS=24000000 main.c -o main.ihx
```
