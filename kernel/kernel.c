#include "screen.h"
#include "string.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
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

    /*
    for (int i = 0; i < 30; i++){
        print_at("Cians first kernel", 0, i);
        //char num = i + '0';
        print(int_to_char(i));
        //print_char(num, -1, -1, 0x0f);
    }*/
    
    /* Fill up the screen */
    /*
    int i = 0;
    for (i = 0; i < 24; i++) {
        print_at(int_to_char(i), 0, i);
    }

    print_at("This text forces the kernel to scroll. Row 0 will disappear. ", 60, 24);
    print("And with this text, the kernel will scroll again, and row 1 will disappear too!");
    */
    isr_install();
    /* Test the interrupts */
    __asm__ __volatile__("int $2");
    __asm__ __volatile__("int $3");
    // TODO int to ascii function
    // TODO handle_scrolling function
}
