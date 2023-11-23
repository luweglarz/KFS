#include "descriptor_tables.h"
#include "klib.h"

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

	gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF); // Kernel Code Segment 
	gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF); // Kernel Data Segment
	gdt_set_gate(3, 0, 0xFFFFFFFF, 0xFA, 0xCF); // User Code Segment
	gdt_set_gate(4, 0, 0xFFFFFFFF, 0xF2, 0xCF); // User Data Segment


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

	idt_set_gate(32, (unsigned long)irq0, 0x08, 0x8E);
	idt_set_gate(33, (unsigned long)irq1, 0x08, 0x8E);

	idt_flush((unsigned long)&idt_ptr);
	asm volatile("sti");
}

static void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags)
{
	idt_entries[num].base_low = base & 0xFFFF;
	idt_entries[num].base_high = (base >> 16) & 0xFFFF;

	idt_entries[num].selector     = sel;
	idt_entries[num].zero = 0;
	idt_entries[num].flags   = flags | 0x60;
}
