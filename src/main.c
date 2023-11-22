#include "klib.h"
#include "descriptor_tables.h"
#include "keyboard.h"
#include "kscreen.h"
#include "shell.h"

int main(void){
   init_descriptor_tables();
   init_keyboard();
   init_shell();

   for(;;);
}
