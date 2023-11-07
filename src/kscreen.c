#include "vga.h"

unsigned short *vga_area_head = ((unsigned short*)VGA_AREA);

 void clear_screen(){
    while (vga_area_head != ((unsigned short*)VGA_AREA)){
        *vga_area_head = VGA_BG(BLACK_COLOUR, 0);
        vga_area_head--;
    }
    *vga_area_head = VGA_BG(BLACK_COLOUR, 0);
    vga_area_head--;
 }