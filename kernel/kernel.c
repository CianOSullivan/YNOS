#include "../drivers/screen.h"
#include "string.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
/* Check if the compiler thinks you are targeting the wrong operating system. */
#if defined(__linux__)
#error "You are not using a cross-compiler, this kernel requires a cross compiler"
#endif

/* This tutorial will only work for the 32-bit ix86 targets. */
#if !defined(__i686__)
#error "This kernel needs to be compiled with a i686-elf compiler"
#endif
void some_function() {

}

void kmain() {
    clear_screen();

    /* Fill up the screen */
    /*
    int i = 0;
    for (i = 0; i < 24; i++) {
        print_at(int_to_char(i), 0, i);
    }

    */
    isr_install(); // Setup the Interrupt Service Routine
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
