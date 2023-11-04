#ifndef KERNEL_H
# define KERNEL_H


# define VGA_TEXT(COLOR, BRIGHT, ASCII) ((COLOR + ((BRIGHT == 1) ? 8 : 0)) << FORE_COLOUR_OFFSET | ASCII)

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