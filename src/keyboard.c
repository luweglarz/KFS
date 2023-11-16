#include "kernel.h"
#include "vga.h"
#include "descriptor_tables.h"
#include "isr.h"

void keyboardHandler(registers_t regs)
{
	char scanCode = inb(0x60) & 0x7F;
   	kputchar(scanCode);

}

void initKeyboard()
{
	register_interrupt_handler(33, &keyboardHandler);
}

	
