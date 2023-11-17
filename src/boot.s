MAGIC_NUMBER equ 0x1BADB002 
FLAGS        equ 0x0
CHECKSUM     equ -MAGIC_NUMBER
STACK_SIZE   equ 4096

section .multiboot_header:
align 4
  dd MAGIC_NUMBER 
  dd FLAGS
  dd -MAGIC_NUMBER - FLAGS

section .text:

extern main

global start_kernel

start_kernel:
  call main
