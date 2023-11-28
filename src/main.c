#include "klib.h"
#include "descriptor_tables.h"
#include "keyboard.h"
#include "kscreen.h"
#include "shell.h"

extern void stack_frame(void);

int main(void){
   init_descriptor_tables();
   init_keyboard();
   init_shell();

   stack_frame();

   for(;;);
}
