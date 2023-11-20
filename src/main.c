#include "kernel.h"
#include "vga.h"
#include "descriptor_tables.h"
#include "keyboard.h"
#include "kscreen.h"

int main(void){
   char buff[124];
    kprintf(kitoa(42, buff));
    kprintf("kitoa(42, buff)\n");
    kprintf("kitoa(42, buff)\n");
    init_descriptor_tables();
    initKeyboard();
    init_cursor(0xB, 0xC); // Maybe using inb() to get Maximum Scan Line Register (Index 0x09) can be good

    //asm volatile ("int $0x3");
   // asm volatile("int $0x4");
   for(;;);
}
