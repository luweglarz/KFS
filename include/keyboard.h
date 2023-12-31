#ifndef KEYBOARD_H
# define KEYBOARD_H

#include "isr.h"

#define ARROW_UP 0x48
#define ARROW_DOWN 0x50
#define ARROW_LEFT 0x4B
#define ARROW_RIGHT 0x4D
#define SHIFT_LEFT 0x2A
#define SHIFT_RIGHT 0x37
#define KEY_LOCK 0x3A
#define BACKSPACE 0x0E
#define ENTER 0x1C

void init_keyboard(void);
void keyboard_handler(registers_t regs);

#endif
