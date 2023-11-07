#include "vga.h"

unsigned short *vga_area_head = ((unsigned short*)VGA_AREA);

void print_ascii(char c){
    if (vga_area_head == (unsigned short*)(VGA_AREA + VGA_TEXT_MODE_SIZE))
        return ;
    *vga_area_head++ = VGA_ASCII(BLUE_COLOUR, 0, c);
 }

void print_string(char *str){
    while (*str != '\0'){
        print_ascii(*str);
        str++;
    }
 }

 void clear_screen(){
    while (vga_area_head != ((unsigned short*)VGA_AREA)){
        *vga_area_head = VGA_BG(BLACK_COLOUR, 0);
        vga_area_head--;
    }
    *vga_area_head = VGA_BG(BLACK_COLOUR, 0);
    vga_area_head--;
 }