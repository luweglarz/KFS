#include "kernel.h"
#include "vga.h"

int main(void){
    char buff[124];
    kprintf(kitoa(42, buff));
    while(1){
    }
}