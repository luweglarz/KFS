#include "kernel.h"
#include "vga.h"
#include "descriptor_tables.h"
#include "isr.h"

int CapsLock = 0;
int CapsLockStatus = 1;

unsigned char lowercase[128] =
{
	0,  0, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
	'9', '0', '-', '=', '\b',	/* Backspace */
	'\t',			/* Tab */
	'q', 'w', 'e', 'r',	/* 19 */
	't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
	0,			/* 29   - Control */
	'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
	'\'', '`',   0,		/* Left shift */
	'\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
	'm', ',', '.', '/',   0,				/* Right shift */
	'*',
	0,	/* Alt */
	' ',	/* Space bar */
	0,	/* Caps lock */
	0,	/* 59 - F1 key ... > */
	0,   0,   0,   0,   0,   0,   0,   0,
	0,	/* < ... F10 */
	0,	/* 69 - Num lock*/
	0,	/* Scroll Lock */
	0,	/* Home key */
	0,	/* Up Arrow */
	0,	/* Page Up */
	'-',
	0,	/* Left Arrow */
	0,
	0,	/* Right Arrow */
	'+',
	0,	/* 79 - End key*/
	0,	/* Down Arrow */
	0,	/* Page Down */
	0,	/* Insert Key */
	0,	/* Delete Key */
	0,   0,   0,
	0,	/* F11 Key */
	0,	/* F12 Key */
	0,	/* All other keys are undefined */
};		

unsigned char uppercase[128] =
{
	0,  0, '!','@','#','$','%','^','&','*','(',')','_','+','\b','\t',			/* Tab */
	'Q','W','E','R','T','Y','U','I','O','P','{','}','\n'
,	/* Enter key */
	0,			/* 29   - Control */
	'A','S','D','F','G','H','J','K','L',':','"','~',0,	/* 39 */
	 		/* Left shift */
	'|','Z','X','C', 'V','B','N','M','<','>','?',0,				/* Right shift */
	'*',
	0,	/* Alt */
	' ',	/* Space bar */
	0,	/* Caps lock */
	0,	/* 59 - F1 key ... > */
	0,   0,   0,   0,   0,   0,   0,   0,
	0,	/* < ... F10 */
	0,	/* 69 - Num lock*/
	0,	/* Scroll Lock */
	0,	/* Home key */
	0,	/* Up Arrow */
	0,	/* Page Up */
	'-',
	0,	/* Left Arrow */
	0,
	0,	/* Right Arrow */
	'+',
	0,	/* 79 - End key*/
	0,	/* Down Arrow */
	0,	/* Page Down */
	0,	/* Insert Key */
	0,	/* Delete Key */
	0,   0,   0,
	0,	/* F11 Key */
	0,	/* F12 Key */
	0,	/* All other keys are undefined */
};

void keyboardHandler(registers_t regs)
{
	unsigned char scanCode = inb(0x60) & 0x7F;

	if (scanCode & 0x80)
	{
	}
	else
	{
		if (scanCode == 0x3A)
		{	
			if(CapsLockStatus == 1)
				CapsLock += 1;
			else
				CapsLock -= 1;
		}
		if(CapsLock == 2 || CapsLock == 0)
		{
			if (CapsLock == 2)
				CapsLockStatus = 0;
			else
				CapsLockStatus = 1;
		}
		if (lowercase[scanCode] != 0 && lowercase[scanCode] != '\b' && lowercase[scanCode] != '\n')
		{
			if(CapsLock == 2)
				kputchar(uppercase[scanCode]);
			else
				kputchar(lowercase[scanCode]);
		}
	}
}

void initKeyboard()
{
	register_interrupt_handler(33, &keyboardHandler);
}


