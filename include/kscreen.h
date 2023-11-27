#ifndef SCREEN_H
# define SCREEN_H

#include "keyboard.h"

extern int ktext_color;
extern int kbg_color;

void change_bg_color();
void init_cursor(uint8_t sl_start, uint8_t sl_end);
void move_cursor(int direction);

#endif 