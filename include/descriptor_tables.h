#ifndef DESCRIPTOR_TABLES_H
# define DESCRIPTOR_TABLES_H

#include "kernel.h"

#define DATA_KEYBOARD 0x60

struct gdt_entry_struct
{
   unsigned short limit_low;           
   unsigned short base_low;            
   unsigned char  base_middle;         
   unsigned char  access;             
   unsigned char  flags;
   unsigned char  base_high;          
} __attribute__((packed));
typedef struct gdt_entry_struct gdt_entry_t;

struct gdt_ptr_struct
{
   unsigned short limit;              
   unsigned long  base;            
}  __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;

struct idt_entry_struct
{
   unsigned short base_low;            
   unsigned short selector;            
   unsigned char  zero;             
   unsigned char  flags;
   unsigned short base_high;          

} __attribute__((packed));
typedef struct idt_entry_struct idt_entry_t;


struct idt_ptr_struct
{
   unsigned short limit;              
   unsigned long  base;            
}  __attribute__((packed));
typedef struct idt_ptr_struct idt_ptr_t;


void init_descriptor_tables();

static inline void outb(unsigned short port, unsigned char val)
{
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) : "memory");
}

static inline unsigned char inb(unsigned short port)
{
    unsigned char ret;
    asm volatile ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port)
                   : "memory");
    return ret;
}

extern void irq0 ();
extern void irq1 ();
#endif
