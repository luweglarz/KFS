#ifndef SHELL_H
# define SHELL_H

#include "klib.h"

struct kprompt{
    char        buffer[3993];
    uint16_t    size;
};
typedef struct kprompt kprompt;

extern kprompt prompt;

void init_shell();
void catch_entry(char c);

#endif