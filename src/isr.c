#include "descriptor_tables.h"
#include "isr.h"
#include "kernel.h"

extern void isr_handler(registers_t);
extern void irq_handler(registers_t);
isr_t interrupt_handlers[256];

void register_interrupt_handler(unsigned char n, isr_t handler)
{
	interrupt_handlers[n] = handler;
}

void isr_handler(registers_t regs)
{
	char buff[50];
	kprintf("recieved interrupt: ");
	kprintf(kitoa(regs.int_no, buff));
	kprintf("\n");
}

void irq_handler(registers_t regs)
{
	if (regs.int_no >= 40)
	{
		outb(0xA0, 0x20);
	}
	outb(0x20, 0x20);

	if (interrupt_handlers[regs.int_no] != 0)
	{
		isr_t handler = interrupt_handlers[regs.int_no];
		handler(regs);
	}
}


