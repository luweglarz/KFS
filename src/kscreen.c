#include "vga.h"

unsigned short *vga_area_head = ((unsigned short*)VGA_AREA);

 void clear_screen(){
    unsigned int x = 0;
    unsigned int y = 0;

    while (y < VGA_HEIGHT){
        x = 0;
        while (x < VGA_WIDTH){
            *((unsigned short*)VGA_AREA + VGA_POSITION(x, y)) = VGA_BG(BLACK_COLOUR, 0);
            x++;
        }
        y++;
    }
    vga_area_head = ((unsigned short*)VGA_AREA) ;    
 }