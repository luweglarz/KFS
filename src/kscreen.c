#include "vga.h"
#include "kernel.h"
#include "descriptor_tables.h"
#include "keyboard.h"

uint16_t *vga_area_head = ((uint16_t*)VGA_AREA);
uint16_t cursor_pos = 0;

void clear_screen(){
    unsigned int x = 0;
    unsigned int y = 0;

    while (y < VGA_HEIGHT){
        x = 0;
        while (x < VGA_WIDTH){
            *((uint16_t*)VGA_AREA + VGA_POSITION(x, y)) = VGA_BG(BLACK_COLOUR, 0);
            x++;
        }
        y++;
    }
    vga_area_head = ((uint16_t*)VGA_AREA) ;    
}

void init_cursor(uint8_t sl_start, uint8_t sl_end){
    outb(0x3D4, 0x0A);                              // Telling VGA controller that we work on Cursor Start register (0x0A)
	outb(0x3D5, (inb(0x3D5) & 0xC0) | sl_start);    // Modifying Cursor Scan Line Start
 
	outb(0x3D4, 0x0B);                              // Telling VGA controller that we work on Cursor End register (0x0A)
	outb(0x3D5, (inb(0x3D5) & 0xE0) | sl_end);      // Modifying Cursor Scan Line End
}

static uint16_t get_cursor_pos(){
    uint16_t cursor_pos = (uint16_t)vga_area_head;
    cursor_pos -= (uint16_t)VGA_AREA;
    cursor_pos /= 2;
    return (cursor_pos);
}

void update_head_cursor(){
    cursor_pos = get_cursor_pos();

    outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) (cursor_pos >> 8) & 0xFF);
    outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) cursor_pos & 0xFF);
}

void move_cursor(int direction){
    if (direction == ARROW_RIGHT)
        vga_area_head++;
    else if (direction == ARROW_LEFT)
        vga_area_head--;
    else if (direction == ARROW_UP)
        vga_area_head -= (1 * VGA_WIDTH * 2);
    else if (direction == ARROW_DOWN)
        vga_area_head += (1 * VGA_WIDTH * 2);
    update_head_cursor();
}