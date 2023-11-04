#include <kernel.h>

void print_letter(char c){
    short letter = VGA_TEXT(BLUE_COLOUR,  0, c);
    *((unsigned int*)VGA_AREA) = letter;

    // We can add background color this way
    //*((unsigned int*)VGA_AREA) = (0x4 << 12) | letter;
 }

int main(void){
    print_letter('C');
    while(1){
    }
}