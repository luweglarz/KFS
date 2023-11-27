#include "klib.h"

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
