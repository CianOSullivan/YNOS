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
    //irq_install();
    /* Test the interrupts */
    //asm volatile("int $2");
    //asm volatile("int $3");

    //asm volatile("sti");
    //init_timer(50);
    /* Comment out the timer IRQ handler to read
     * the keyboard IRQs easier */
    //init_keyboard();
    print("Type something, it will go through the kernel\nType END to halt the CPU\n> ");
    start_shell();
}

