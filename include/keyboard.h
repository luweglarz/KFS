#ifndef KEYBOARD_H
# define KEYBOARD_H

#include "isr.h"

#define CURSOR_UP 0x48
#define CURSOR_DOWN 0x50
#define CURSOR_LEFT 0x4B
#define CURSOR_RIGHT 0x4D
#define SHIFT_LEFT 0x2A
#define SHIFT_RIGHT 0x37
#define KEY_LOCK 0x3A



void initKeyboard(void);
void keyboardHandler(registers_t regs);

#endif
