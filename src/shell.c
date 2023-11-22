#include "shell.h"
#include "vga.h"
#include "klib.h"
#include "builtin.h"

kprompt     prompt;
kbuiltin    builtin[1] = {
    {"reboot\0", &reboot}, 
};

void catch_entry(char c){
    prompt.buffer[prompt.size] = c;
    prompt.size++;
}

void exec_cmd(){
    int i = 0;

    while (i < 1){
        if (kstrncmp(prompt.buffer, builtin[i].name, kstrlen(builtin[i].name)) == 0)
            builtin[i].builtin_func();
        i++;
    }
    vga_area_head = (uint16_t*)VGA_JMP_LINE;
    init_shell();
}

void init_shell(){
    kmemset(prompt.buffer, '\0', sizeof(prompt.buffer));
    prompt.size = 0;
    kprintf("kshell>", GREEN_COLOR, 0);
}