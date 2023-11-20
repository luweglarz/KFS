#include "kernel.h"
#include "vga.h"
#include "descriptor_tables.h"
#include "keyboard.h"

int main(void){
   // char buff[124];
   // kprintf(kitoa(42, buff));
    init_descriptor_tables();
    initKeyboard();

   for(;;);
}
