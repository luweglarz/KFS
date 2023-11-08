#include "vga.h"

void kputchar(char c){
    if (vga_area_head == (unsigned short*)(VGA_AREA + (VGA_WIDTH * VGA_HEIGHT)))
        return ;
    *vga_area_head = VGA_ASCII(BLUE_COLOUR, 0, c);
    vga_area_head++;
 }

unsigned int kprintf(char *str){
    int cnt = 0;

    while (*str != '\0'){
        if (*str == '\n'){
            vga_area_head = (unsigned short*)VGA_JMP_LINE;
            str++;
            continue ;
        }
        kputchar(*str);
        str++;
        cnt++;
    }
    return (cnt);
 }