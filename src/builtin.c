#include "klib.h"
 
int reboot()
{
    /* 
        0x64 :  PS/2 command register port 
        0xFE :  reset CPU command 
    */
    outb(0x64, 0xFE);
    return (0);
}