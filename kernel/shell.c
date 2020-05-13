#include "shell.h"

void start_shell() {
    /* Enable interruptions */
    asm volatile("sti");
    /* IRQ0: timer */
    init_timer(50);
    /* IRQ1: keyboard */
    init_keyboard();
    //char s[] = "my name is this";
    //char* delm = " ";
    //char newstr[100];
    //char *str = strtok(s, delm);
    //while(str){
    //    print(str);
    //    print("\n");
    //    str = strtok(s, delm);
    //}
}

void user_input(char *input) {
    char* inputArray[10];
    argparse(input, inputArray);

    int c = 0;
    while (strcmp(inputArray[c], '\0') != 0) {
      print(inputArray[c++]);
      print("\n");
    }

    if (strcmp(input, "END") == 0 || strcmp(input, "EXIT") == 0 ) {
        print("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    } else if (strcmp(input, "HELP") == 0) {
    	print("Command Help\n\n");
        print("The following commands can be run:\n\n");
        print("    END or EXIT - Halt the CPU\n");
        print("    HELP - Display this help message\n");
        print("    PAGE - Allocate more memory to the running program\n\n");
    } else if (strcmp(input, "PAGE") == 0) {
        u32 phys_addr;
        u32 page = kmalloc(1000, 1, &phys_addr);
        char page_str[16] = "";
        hex_to_ascii(page, page_str);
        char phys_str[16] = "";
        hex_to_ascii(phys_addr, phys_str);
        print("Page: ");
        print(page_str);
        print(", physical address: ");
        print(phys_str);
        print("\n");
    } else if (strcmp(input, "SPLIT") == 0) {

        char str[] ="This a sample string";
        char* pch;
        print("Splitting string ");
        print(str);
        print(" into tokens:\n");
        pch = strtok(str," ");
        while (pch != NULL)
        {
            print(pch);
            print("\n");
            pch = strtok(NULL, " ");
        }
    }
    print("> ");
}

void argparse(char *input, char* inputArray[]) {
    // Parse arguments
    int i = 0;
    char* pch;
    pch = strtok(input," ");
    inputArray[i++] = pch;

    while (pch != NULL)
    {
        // inputArray has a size of 10
        // Change this to accept more arguments?
        if (i > 9) {
            print("This input has too many arguments\n");
            break;
        }
        pch = strtok(NULL, " ");
        inputArray[i++] = pch;
    }
}
