#include "vga.h"

void kputchar(char c){
    if (vga_area_head == (VGA_AREA + VGA_TEXT_MODE_SIZE))
        return ;
    *vga_area_head = VGA_ASCII(BLUE_COLOUR, 0, c);
    vga_area_head++;
 }

unsigned int kprintf(char *str){
    int cnt = 0;

    while (*str != '\0'){
        if (*str == '\n'){
            vga_area_head = VGA_AREA + (1 * 80 * 2);
            str++;
            continue ;
        }
        kputchar(*str);
        str++;
        cnt++;
    }
    return (cnt);
 }