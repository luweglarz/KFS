#include "shell.h"
#include "vga.h"

kprompt prompt;

void catch_entry(char c){
    prompt.buffer[prompt.size] = c;
    prompt.size++;
}

void init_shell(){
    kmemset(prompt.buffer, '\0', sizeof(prompt.buffer));
    prompt.size = 0;
    kprintf("kshell>", GREEN_COLOR, 0);
}