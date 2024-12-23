#include <8051.h>

#define BOOT_ADDR  0x3800

void main( void ) 
{
	// Disable all interrupts.
	EA = 0;
	
	__asm
		LJMP BOOT_ADDR // Jump to bootloader.
	__endasm;
	while(1); 
}
