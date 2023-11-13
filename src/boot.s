MAGIC_NUMBER equ 0x1BADB002 
FLAGS        equ 0x0
CHECKSUM     equ -MAGIC_NUMBER
STACK_SIZE   equ 4096

section .multiboot_header:
align 4
  dd 0x1BADB002 
  dd 0x0
  dd -MAGIC_NUMBER - 0x0

section .text:

extern main

global start_kernel
global gdt_flush
global idt_flush


start_kernel:
  call main

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
