MAGIC_NUMBER equ 0x1BADB002 
FLAGS        equ 0x0
CHECKSUM     equ -MAGIC_NUMBER

section .multiboot_header:
align 4
  dd MAGIC_NUMBER
  dd FLAGS
  dd CHECKSUM

section .text:
global start_kernel

extern main

start_kernel:
  mov esp, stack_floor ; ESP point to the bottom of the stack
  call main
  add esp, 4 ; Add call ret value to esp register
  pop eax ; pop ret into eax register

section .data:

section .bss:
stack_floor resb 4096 ; Allocate 4KB for the stack