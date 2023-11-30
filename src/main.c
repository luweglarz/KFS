#include "klib.h"
#include "descriptor_tables.h"
#include "keyboard.h"
#include "kscreen.h"
#include "shell.h"

extern void stack_frame(void);

void loop_f(void)
{
  print_stack_kernel(20);
  for(;;);
}

int main(void){
   init_descriptor_tables();
   init_keyboard();
   init_shell();

//   loop_f();

   print_stack_kernel(20);
   for(;;);
}

