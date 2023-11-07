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

start_kernel:
  mov esp, stack_floor 
  call main

section .bss:
stack_floor resb STACK_SIZE ; Allocate 4KB for the stack