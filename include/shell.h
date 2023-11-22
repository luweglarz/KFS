#ifndef SHELL_H
# define SHELL_H

#include "klib.h"

typedef struct  s_kprompt{
    char        buffer[3993];
    uint16_t    size;
}               kprompt;

extern kprompt prompt;

typedef struct  s_kbuiltin{
    const char    name[128];
    int     (*builtin_func)();
}               kbuiltin;

extern kbuiltin builtin[1];


void init_shell();
void catch_entry(char c);
void exec_cmd();

#endif