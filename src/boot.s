MAGIC_NUMBER equ 0x1BADB002 
FLAGS        equ 0x0
CHECKSUM     equ -MAGIC_NUMBER

section .multiboot_header:
align 4
  dd MAGIC_NUMBER 
  dd FLAGS
  dd -MAGIC_NUMBER - FLAGS

section .text:

extern main
extern irq_handler

global start_kernel
global gdt_flush
global idt_flush

gdt_flush:
   mov eax, [esp+4]  
   lgdt [eax]        

   mov ax, 0x10      
   mov ds, ax       
   mov es, ax
   mov fs, ax
   mov gs, ax
   mov ss, ax
   jmp 0x08:.flush   
.flush:
   ret

idt_flush:
   mov eax, [esp+4]
   lidt [eax]
   ret

%macro IRQ 2
  global irq%1
  irq%1:
    cli
    push byte 0
    push byte %2
    jmp irq_common_stub
%endmacro


IRQ   0,    32
IRQ   1,    33

irq_common_stub:
   pusha       

   mov ax, ds 
   push eax 

   mov ax, 0x10 
   mov ds, ax
   mov es, ax
   mov fs, ax
   mov gs, ax

   call irq_handler

   pop ebx    
   mov ds, bx
   mov es, bx
   mov fs, bx
   mov gs, bx

   popa    
   add esp, 8
   sti
   iret    

start_kernel:
  call main