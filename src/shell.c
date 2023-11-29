#include "shell.h"
#include "vga.h"
#include "klib.h"
#include "builtin.h"
#include "kscreen.h"

kprompt     prompt;
kbuiltin    builtin[BUILTINS_SIZE] = {
    {"reboot\0", &reboot}, {"halt\0", &halt}, {"cbgcolor\0", &cbgcolor}, {"ctcolor\0", &ctcolor}, {"clear\0", &clear}
};

void catch_entry(char c){
    prompt.buffer[prompt.size] = c;
    kputchar(prompt.buffer[prompt.size] , ktext_color, 1);
    prompt.size++;
}

void remove_entry(){
    if (prompt.size == 0)
        return ;
    prompt.buffer[prompt.size] = '\0';
    prompt.size--;
    move_cursor(ARROW_LEFT);
    kputchar('\0', ktext_color, 1);
    move_cursor(ARROW_LEFT);
}

void exec_cmd(){
    int i = 0;

    vga_area_head = (uint16_t*)VGA_JMP_LINE;
    while (i < BUILTINS_SIZE){
        if (kstrncmp(prompt.buffer, builtin[i].name, kstrlen(builtin[i].name)) == 0 
            && kstrlen(builtin[i].name) == prompt.size){
            builtin[i].builtin_func(0);
            break ;
        }
        else if (kstrncmp(prompt.buffer, builtin[i].name, kstrlen(builtin[i].name)) == 0){
            char *arg = prompt.buffer + kstrlen(builtin[i].name);
            while (*arg == ' ')
                arg++;
            builtin[i].builtin_func(arg);
            break ;
        }
        i++;
    }
    init_shell();
}

void init_shell(){
    kmemset(prompt.buffer, '\0', sizeof(prompt.buffer));
    prompt.size = 0;
    if (kbg_color == GREEN_COLOR)
        kprintf("kshell>", BLACK_COLOR, 0);
    else
        kprintf("kshell>", GREEN_COLOR, 0);
}