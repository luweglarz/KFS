#include "vga.h"
#include "klib.h"
#include "descriptor_tables.h"
#include "keyboard.h"
#include "kscreen.h"

uint16_t *vga_area_head = ((uint16_t*)VGA_AREA);
int ktext_color = LIGHT_GRAY_COLOR;
int kbg_color = BLACK_COLOR;

void change_bg_color(int color, int bright){
    unsigned int x = 0;
    unsigned int y = 0;
    char save_char = 0;

    while (y < VGA_HEIGHT){
        x = 0;
        while (x < VGA_WIDTH){
            *((uint16_t*)VGA_AREA + VGA_POSITION(x, y)) = VGA_BG(color, bright);
            x++;
        }
        y++;
    }
    vga_area_head = ((uint16_t*)VGA_AREA);
}

void init_cursor(uint8_t sl_start, uint8_t sl_end){
    outb(0x3D4, 0x0A);                              
	outb(0x3D5, (inb(0x3D5) & 0xC0) | sl_start); 
 
	outb(0x3D4, 0x0B);                             
	outb(0x3D5, (inb(0x3D5) & 0xE0) | sl_end);
}

static uint16_t get_cursor_pos(){
    uint16_t cursor_pos = (uint16_t)vga_area_head;
    cursor_pos -= (uint16_t)VGA_AREA;
    cursor_pos /= 2;
    return (cursor_pos);
}

static void update_head_cursor(){
    uint16_t cursor_pos = get_cursor_pos();

    outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) (cursor_pos >> 8) & 0xFF);
    outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) cursor_pos & 0xFF);
}

void move_cursor(int direction){
    uint16_t cursor_pos = get_cursor_pos();

    if (direction == ARROW_RIGHT && (cursor_pos + 1) < (VGA_HEIGHT * VGA_WIDTH) / 2)
        vga_area_head++;
    else if (direction == ARROW_LEFT && cursor_pos - 1 >= 0)
        vga_area_head--;
    else if (direction == ARROW_UP && (cursor_pos - VGA_WIDTH) >= 0)
        vga_area_head -= VGA_WIDTH;
    else if (direction == ARROW_DOWN && (cursor_pos + VGA_WIDTH) < (VGA_HEIGHT * VGA_WIDTH) / 2)
        vga_area_head += VGA_WIDTH;
    update_head_cursor();
}