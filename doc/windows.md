# Sobrevivir en Windows 11

Para desarrollar y compilar se puede hacer en WSL, pero no es transparente, se deben tener varios puntos bajo control: 

## Puerto USB

usbipd list

Connected:
BUSID  VID:PID    DEVICE                                                        STATE
2-2    041e:40a3  Creative Live! Cam Sync V3, Creative Live! Cam Sync V3 Mic    Not shared
3-7    4348:55e0  USB Module                                                    Shared
3-11   048d:5702  USB Input Device                                              Not shared
3-12   0bda:0852  Generic Bluetooth Adapter                                     Not shared
4-2    0bda:8156  Realtek USB 2.5GbE Family Controller                          Not shared
4-3    05ac:029c  USB Input Device                                              Not shared
4-5    0bda:1100  USB Input Device                                              Not shared
5-2    046d:c548  Logitech USB Input Device, USB Input Device                   Not shared


usbipd bind --busid 3-7


usbipd attach --wsl --busid 3-7 --auto-attach

