#include "kernel.h"
#include "vga.h"
#include "descriptor_tables.h"

int main(void){
    char buff[124];
    kprintf(kitoa(42, buff));
    init_descriptor_tables();

    asm volatile ("int $0x3");
    asm volatile("int $0x4");
    while(1){
    }
}
