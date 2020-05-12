#include "shell.h"

void start_shell() {
    /* Enable interruptions */
    asm volatile("sti");
    /* IRQ0: timer */
    init_timer(50);
    /* IRQ1: keyboard */
    init_keyboard();
}

void user_input(char *input) {
    argparse(input);
    if (strcmp(input, "END") == 0) {
        print("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    } else if (strcmp(input, "HELP") == 0) {
    	print("Displaying help.\n");
    }
    print("You said: ");
    print(input);
    print("\n> ");
}

void argparse(char *input) {
    // Parse arguments
}
