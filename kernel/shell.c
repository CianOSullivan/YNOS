#include "shell.h"

const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6",
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E",
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl",
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`",
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".",
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G',
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

void keyboard_callback() {
    /* The PIC leaves us the scancode in port 0x60 */
    u8 scancode = port_byte_in(0x60);

    if (scancode > SC_MAX) return;
    if (scancode == BACKSPACE) {
        backspace(key_buffer);
        print_backspace();
    } else if (scancode == ENTER) {
        print("\n");
        user_input(key_buffer); /* kernel-controlled function */
        key_buffer[0] = '\0';
    } else {
        char letter = sc_ascii[(int)scancode];
        /* Remember that print only accepts char[] */
        char str[2] = {letter, '\0'};
        append(key_buffer, letter);
        print(str);
    }
}

void init_keyboard() {
   register_interrupt_handler(IRQ1, keyboard_callback);
}

void cowsay(char* inputArray[], int argc) {
    if (argc == 1) {
        print("< moOh >\n");
    } else {
        //int c = 1;
        //while (strcmp(inputArray[c], '\0') != 0) {
        //    print(inputArray[c++]);
        //    print("\n");
        //}

        for (int i = 1; i < argc; i++) {
            if (i == 1) {
                print("/");
                print(inputArray[i]);
                print("\\\n");
            }
            else if (i == argc - 1) {
                print("\\ ");
                print(inputArray[i]);
                print("/\n");
            }
            else {
                print("| ");
                print(inputArray[i]);
                print("|\n");
            }

        }
    }
    print("   \\\n");
    print("     \\ ^__^\n");
    print("       (oo)\\_______\n");
    print("       (__)\\       )\\/\\\n");
    print("           ||----w |\n");
    print("           ||     ||\n");
}

void start_shell() {
    /* Enable interruptions */
    asm volatile("sti");
    /* IRQ0: timer */
    init_timer(50);
    /* IRQ1: keyboard */
    init_keyboard();
}

void user_input(char *input) {
    char* inputArray[10];
    int argc = argparse(input, inputArray);

    //print_int("", argc);
    //int c = 0;
    //while (strcmp(inputArray[c], '\0') != 0) {
    //  print(inputArray[c++]);
    //  print("\n");
    //}

    if (strcmp(inputArray[0], "END") == 0 || strcmp(input, "EXIT") == 0 ) {
        print("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    } else if (strcmp(inputArray[0], "HELP") == 0) {
    	print("Command Help\n\n");
        print("The following commands can be run:\n\n");
        print("    CLEAR - Clear the screen\n");
        print("    COWSAY [MESSAGE] - Make a cow say a message\n");
        print("    END or EXIT - Halt the CPU\n");
        print("    HELP - Display this help message\n");
        print("    PAGE - Allocate more memory to the running program\n");
        print("    DECTOHEX - Convert the given number to hexadecimal\n");
        print("\n");
    } else if (strcmp(inputArray[0], "PAGE") == 0) {
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
    } else if (strcmp(inputArray[0], "HEX") == 0) {
        // run hex_to_ascii on first argument
        char str[1];
        hex_to_ascii(41, str);
        print("ASCII: ");
        char a = (int) str;
        //print(a);
    } else if (strcmp(inputArray[0], "COWSAY") == 0) {
        cowsay(inputArray, argc);
    } else if (strcmp(inputArray[0], "CLEAR") == 0) {
        clear_screen();
    }
    print("> ");
}

int argparse(char *input, char* inputArray[]) {
    // Parse arguments
    int i = 0;
    char* pch;
    pch = strtok(input, " ");
    inputArray[i] = pch;

    while (pch != NULL)
    {
        i++;
        // inputArray has a size of 10
        // Change this to accept more arguments?
        if (i > 9) {
            print("This input has too many arguments\n");
            break;
        }
        pch = strtok(NULL, " ");
        inputArray[i] = pch;
    }
    return i;
}
