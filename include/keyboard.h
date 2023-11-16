#ifndef KEYBOARD_H
# define KEYBOARD_H

#include "isr.h"

void initKeyboard(void);
void keyboardHandler(registers_t regs);

#endif
