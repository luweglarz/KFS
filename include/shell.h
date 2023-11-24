#ifndef SHELL_H
# define SHELL_H

#include "klib.h"

# define BUILTINS_SIZE 3

typedef struct  s_kprompt{
    char        buffer[3993];
    uint16_t    size;
}               kprompt;

extern kprompt prompt;

typedef struct  s_kbuiltin{
    const char    name[128];
    void          (*builtin_func)();
}               kbuiltin;

extern kbuiltin builtin[BUILTINS_SIZE];

void init_shell();
void catch_entry(char c);
void exec_cmd();
void remove_entry();

#endif