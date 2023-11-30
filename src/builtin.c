#include "klib.h"
#include "kscreen.h"
#include "builtin.h"
#include "shell.h"

void reboot()
{
    /* 
        0x64 :  PS/2 command register port 
        0xFE :  reset CPU command 
    */
    outb(0x64, 0xFE);
    return (0);
}

void halt(){
    asm( "hlt" );
    return (0);
}

static int check_color(char *color){
    if (kstrncmp(color, "black", kstrlen(color)) == 0)
        return (BLACK_COLOR);
    else if (kstrncmp(color, "blue", kstrlen(color)) == 0)
        return (BLUE_COLOR);
    else if (kstrncmp(color, "green", kstrlen(color)) == 0)
        return (GREEN_COLOR);
    else if (kstrncmp(color, "cyan", kstrlen(color)) == 0)
        return (CYAN_COLOR);
    else if (kstrncmp(color, "red", kstrlen(color)) == 0)
        return (RED_COLOR);
    else if (kstrncmp(color, "magenta", kstrlen(color)) == 0)
        return (MAGENTA_COLOR);
    else if (kstrncmp(color, "brown", kstrlen(color)) == 0)
        return (BROWN_COLOR);
    else if (kstrncmp(color, "gray", kstrlen(color)) == 0)
        return (LIGHT_GRAY_COLOR);
    return (-1);
}

void cbgcolor(char *arg){
    int color = check_color(arg);
    if (color == -1){
        kprintf("Wrong argument\n", LIGHT_GRAY_COLOR, 1);
        return ;
    }
    kbg_color = color;
    change_bg_color(color, 0);
}

void ctcolor(char *arg){
    int color = check_color(arg);

    if (color == -1){
        kprintf("Wrong argument\n", LIGHT_GRAY_COLOR, 1);
        return ;
    }
    ktext_color = color;
}

void clear(){
    change_bg_color(kbg_color, 0);
}