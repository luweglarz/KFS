#ifndef VGA_H
# define VGA_H

# include "klib.h"

extern uint16_t *vga_area_head;

# define VGA_WIDTH 80
# define VGA_HEIGHT 50

# define VGA_POSITION(x, y) (y * VGA_WIDTH + x)
# define VGA_JMP_LINE (VGA_AREA + (1 * VGA_WIDTH * 2))

# define VGA_ASCII(COLOR, BRIGHT, ASCII) ((COLOR + ((BRIGHT == 1) ? 8 : 0)) << FORE_COLOR_OFFSET | ASCII)
# define VGA_BG(COLOR, BRIGHT) ((COLOR + ((BRIGHT == 1) ? 8 : 0)) << BACKGROUND_COLOR_OFFSET)

# define VGA_AREA 0xb8000

# define FORE_COLOR_OFFSET 8
# define BACKGROUND_COLOR_OFFSET 12

# define BLACK_COLOR (0x0)
# define BLUE_COLOR (0x1)
# define GREEN_COLOR (0x2)
# define CYAN_COLOR (0x3)
# define RED_COLOR (0x4)
# define RED_COLOR (0x4)
# define MAGENTA_COLOR (0x5)
# define BROWN_COLOR (0x6)
# define LIGHT_GRAY_COLOR (0x7)



#endif