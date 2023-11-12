#include "descriptor_tables.h"

extern void gdt_flush(unsigned long);

static void init_gdt();
static void gdt_set_gate(unsigned long, unsigned long, unsigned long, unsigned char, unsigned char);

gdt_entry_t gdt_entries[5];
gdt_ptr_t   gdt_ptr;


void init_descriptor_tables()
{
   init_gdt();
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
