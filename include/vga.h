#ifndef VGA_H
# define VGA_H

extern unsigned short *vga_area_head;

void            clear_screen();

# define VGA_WIDTH 80
# define VGA_HEIGHT 50

# define VGA_POSITION(x, y) (y * VGA_WIDTH + x)
# define VGA_JMP_LINE (VGA_AREA + (1 * VGA_WIDTH * 2))

# define VGA_ASCII(COLOR, BRIGHT, ASCII) ((COLOR + ((BRIGHT == 1) ? 8 : 0)) << FORE_COLOUR_OFFSET | ASCII)
# define VGA_BG(COLOR, BRIGHT) ((COLOR + ((BRIGHT == 1) ? 8 : 0)) << BACKGROUND_COLOUR_OFFSET)

/* Screen offset*/
# define VGA_AREA 0xb8000

# define FORE_COLOUR_OFFSET 8
# define BACKGROUND_COLOUR_OFFSET 12

/* colors*/
# define BLACK_COLOUR (0x0)
# define BLUE_COLOUR (0x1)
# define GREEN_COLOUR (0x2)
# define CYAN_COLOUR (0x3)
# define RED_COLOUR (0x4)
# define RED_COLOUR (0x4)
# define MAGENTA_COLOUR (0x5)
# define BROWN_COLOUR (0x6)
# define LIGHT_GRAY_COLOUR (0x7)



#endif