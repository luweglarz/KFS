#include "klib.h"
#include "vga.h"
#include "descriptor_tables.h"
#include "isr.h"
#include "keyboard.h"
#include "kscreen.h"
#include "shell.h"

int caps_lock = 0;
int caps_on = 0;

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

static void caps_lock_f(unsigned char scan_code, unsigned char press)
{
	if (scan_code == KEY_LOCK && press == 0)
	{
		if(caps_lock == 0)
			caps_lock = 1;
		else
			caps_lock = 0;
	}
}

static void caps_on_f(unsigned char scan_code, unsigned char press)
{
	if (scan_code == SHIFT_LEFT || scan_code == SHIFT_RIGHT)
	{
		if (press == 0)
			caps_on = 1;
		else
			caps_on = 0;
	}
}

static int upper_lower_case_check(unsigned char scan_code, unsigned char press)
{
	caps_lock_f(scan_code, press);
	caps_on_f(scan_code, press);
	if (caps_on == 1 && caps_lock == 0)
		return 1;
	else if(caps_on == 0 && caps_lock == 1)
		return 1;
	else if(caps_on && caps_lock == 1)
		return 0;
	else
		return 0;
}

void keyboard_handler(registers_t regs)
{
	unsigned char scan_code = inb(DATA_KEYBOARD) & 0x7F;
	unsigned char press = inb(DATA_KEYBOARD) & 0x80;
	int ret = upper_lower_case_check(scan_code, press);

	if(press == 0 && (scan_code == ARROW_LEFT || scan_code == ARROW_RIGHT || scan_code == ARROW_UP || scan_code == ARROW_DOWN))
	{
		move_cursor(scan_code);
	}

	if (press == 0 && scan_code == BACKSPACE) {
		remove_entry();
	}

	if(press == 0 && scan_code == ENTER) {
		exec_cmd();
	}

	if (press == 0 && lowercase[scan_code] != 0 && lowercase[scan_code] != '\b' && lowercase[scan_code] != '\n')
	{
		if(ret)
			catch_entry(uppercase[scan_code]);
		else
			catch_entry(lowercase[scan_code]);
	}
}

void init_keyboard()
{
	register_interrupt_handler(33, &keyboard_handler);
}


