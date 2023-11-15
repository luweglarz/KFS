#include "descriptor_tables.h"
#include "isr.h"
#include "kernel.h"

extern void isr_handler(registers_t);

void isr_handler(registers_t regs)
{
	char buff[50];
   kprintf("recieved interrupt: ");
   kprintf(kitoa(regs.int_no, buff));
   kprintf("\n");
}
