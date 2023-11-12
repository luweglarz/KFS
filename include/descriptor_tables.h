#ifndef DESCRIPTOR_TABLES_H
# define DESCRIPTOR_TABLES_H

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
}
 __attribute__((packed));
typedef struct gdt_ptr_struct gdt_ptr_t;

void init_descriptor_tables();

#endif
