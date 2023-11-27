#ifndef SCREEN_H
# define SCREEN_H

#include "keyboard.h"

void clear_screen();
void init_cursor(uint8_t sl_start, uint8_t sl_end);
void move_cursor(int direction);

#endif 