#include "descriptor_tables.h"
#include "kernel.h"

extern void gdt_flush(unsigned long);
extern void idt_flush(unsigned long);


static void init_gdt();
static void gdt_set_gate(unsigned long, unsigned long, unsigned long, unsigned char, unsigned char);

static void init_idt();
static void idt_set_gate(unsigned char, unsigned long, unsigned short, unsigned char);


gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;

idt_entry_t idt_entries[256];
idt_ptr_t   idt_ptr;



void init_descriptor_tables()
{
	init_gdt();
	init_idt();
}

static void init_gdt()
{
	gdt_ptr.limit = (sizeof(gdt_entry_t) * 5) - 1;
	gdt_ptr.base  = (unsigned long)&gdt_entries;

	gdt_set_gate(0, 0, 0, 0, 0);                
	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); 
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF);
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF);

	gdt_flush((unsigned long)&gdt_ptr);
}

static void gdt_set_gate(unsigned long num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran)
{
	gdt_entries[num].base_low    = (base & 0xFFFF);
	gdt_entries[num].base_middle = (base >> 16) & 0xFF;
	gdt_entries[num].base_high   = (base >> 24) & 0xFF;

	gdt_entries[num].limit_low   = (limit & 0xFFFF);
	gdt_entries[num].flags = (limit >> 16) & 0x0F;

	gdt_entries[num].flags |= gran & 0xF0;
	gdt_entries[num].access      = access;
}


static void init_idt()
{
	idt_ptr.limit = (sizeof(idt_entry_t) * 256) - 1;
	idt_ptr.base  = (unsigned long)&idt_entries;

	kmemset(&idt_entries, 0, sizeof(idt_entry_t)*256);

	outb(0x20, 0x11);
	outb(0xA0, 0x11);

	outb(0x21, 0x20);
	outb(0xA1, 0x28);

	outb(0x21, 0x04);
	outb(0xA1, 0x02);

	outb(0x21, 0x01);
	outb(0xA1, 0x01);

	outb(0x21, 0x0);
	outb(0xA1, 0x0);

	idt_set_gate(0, (unsigned long)isr0,0x08, 0x8E);
	idt_set_gate(1, (unsigned long)isr1,0x08, 0x8E);
	idt_set_gate(2, (unsigned long)isr2,0x08, 0x8E);
	idt_set_gate(3, (unsigned long)isr3,0x08, 0x8E);
	idt_set_gate(4, (unsigned long)isr4, 0x08, 0x8E);
	idt_set_gate(5, (unsigned long)isr5, 0x08, 0x8E);
	idt_set_gate(6, (unsigned long)isr6, 0x08, 0x8E);
	idt_set_gate(7, (unsigned long)isr7, 0x08, 0x8E);
	idt_set_gate(8, (unsigned long)isr8, 0x08, 0x8E);
	idt_set_gate(9, (unsigned long)isr9, 0x08, 0x8E);
	idt_set_gate(10, (unsigned long)isr10, 0x08, 0x8E);
	idt_set_gate(11, (unsigned long)isr11, 0x08, 0x8E);
	idt_set_gate(12, (unsigned long)isr12, 0x08, 0x8E);
	idt_set_gate(13, (unsigned long)isr13, 0x08, 0x8E);
	idt_set_gate(14, (unsigned long)isr14, 0x08, 0x8E);
	idt_set_gate(15, (unsigned long)isr15, 0x08, 0x8E);
	idt_set_gate(16, (unsigned long)isr16, 0x08, 0x8E);
	idt_set_gate(17, (unsigned long)isr17, 0x08, 0x8E);
	idt_set_gate(18, (unsigned long)isr18, 0x08, 0x8E);
	idt_set_gate(19, (unsigned long)isr19, 0x08, 0x8E);
	idt_set_gate(20, (unsigned long)isr20, 0x08, 0x8E);
	idt_set_gate(21, (unsigned long)isr21, 0x08, 0x8E);
	idt_set_gate(22, (unsigned long)isr22, 0x08, 0x8E);
	idt_set_gate(23, (unsigned long)isr23, 0x08, 0x8E);
	idt_set_gate(24, (unsigned long)isr24, 0x08, 0x8E);
	idt_set_gate(25, (unsigned long)isr25, 0x08, 0x8E);
	idt_set_gate(26, (unsigned long)isr26, 0x08, 0x8E);
	idt_set_gate(27, (unsigned long)isr27, 0x08, 0x8E);
	idt_set_gate(28, (unsigned long)isr28, 0x08, 0x8E);
	idt_set_gate(29, (unsigned long)isr29, 0x08, 0x8E);
	idt_set_gate(30, (unsigned long)isr30, 0x08, 0x8E);
	idt_set_gate(31, (unsigned long)isr31, 0x08, 0x8E);

/*	idt_set_gate(32, (unsigned long)irq0, 0x08, 0x8E);
	idt_set_gate(33, (unsigned long)irq1, 0x08, 0x8E);
	idt_set_gate(34, (unsigned long)irq2, 0x08, 0x8E);
	idt_set_gate(35, (unsigned long)irq3, 0x08, 0x8E);
	idt_set_gate(36, (unsigned long)irq4, 0x08, 0x8E);
	idt_set_gate(37, (unsigned long)irq5, 0x08, 0x8E);
	idt_set_gate(38, (unsigned long)irq6, 0x08, 0x8E);
	idt_set_gate(39, (unsigned long)irq7, 0x08, 0x8E);
	idt_set_gate(40, (unsigned long)irq8, 0x08, 0x8E);
	idt_set_gate(41, (unsigned long)irq9, 0x08, 0x8E);
	idt_set_gate(42, (unsigned long)irq10, 0x08, 0x8E);
	idt_set_gate(43, (unsigned long)irq11, 0x08, 0x8E);
	idt_set_gate(44, (unsigned long)irq12, 0x08, 0x8E);
	idt_set_gate(45, (unsigned long)irq13, 0x08, 0x8E);
	idt_set_gate(46, (unsigned long)irq14, 0x08, 0x8E);
	idt_set_gate(47, (unsigned long)irq15, 0x08, 0x8E);


	idt_set_gate(128, (unsigned long)isr128, 0x08, 0x8E);
	idt_set_gate(177, (unsigned long)isr177, 0x08, 0x8E);*/


	idt_flush((unsigned long)&idt_ptr);
}

static void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
	idt_entries[num].base_low = base & 0xFFFF;
	idt_entries[num].base_high = (base >> 16) & 0xFFFF;

	idt_entries[num].selector     = sel;
	idt_entries[num].zero = 0;
	idt_entries[num].flags   = flags | 0x60;
}
