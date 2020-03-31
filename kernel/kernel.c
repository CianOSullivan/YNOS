#include "screen.h"
/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, you will most certainly run into trouble"
#endif
 
/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i686__)
#error "This tutorial needs to be compiled with a ix86-elf compiler"
#endif
void some_function() {
    
}

void kmain() {
    clear_screen();
    //printX();
    //print_char('Z', -1, -1, 0x0f); // This works - prints Z at the initial cursor position
    //print_char('Z', -1, -1, 0x0f);
    //print_char('Z', -1, -1, 0x0f);
    //print_char('N', 1, 12, 0x0f);
    //print_at("X", 10, 10);
    for (int i = 0; i < 25; i++){
        print_at("Cians first kernel", 0, i);
        char num = i + '0';
        print_char(num, -1, -1, 0x0f);
    }
    //print_at("XXXX", 1, 11);

    //print("My first kernel");

    //print_at("My first kernel", 0, 12);
    //print_char('!', -1, -1, 0x0f);
    //print_char('Z', 16, 16, 0x0f);


    // TODO int to ascii function
    // TODO handle_scrolling function
}
