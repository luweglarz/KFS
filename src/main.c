#include "klib.h"
#include "descriptor_tables.h"
#include "keyboard.h"
#include "kscreen.h"

int main(void){
   char buff[128];

   kprintf(kitoa(42, buff));
   init_descriptor_tables();
   init_keyboard();

   for(;;);
}
