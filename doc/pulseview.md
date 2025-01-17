# Pulseview

Open Source software for logic analyze development by [sigrok](https://sigrok.org/wiki/PulseView). El dispositivo que uso es el [nanoDLA](https://github.com/wuxx/nanoDLA) que funciona muy bien, asegurate de tenerlo correctamente [configurado](https://github.com/nstrappazzonc/CH552/blob/main/doc/logic_analyze.md).

## Windows

Escriba las siguientes líneas en el PowerShell:

```powershell
winget install pulseview
winget install --id=Microsoft.VCRedist.2010.x64  -e
```

Al iniciar Pulseview, podrá seleccionar el dispositivo para capturar los datos:

![](https://github.com/nstrappazzonc/CH552/blob/main/assets/doc/pulseview/pulseview01.png?raw=true)
