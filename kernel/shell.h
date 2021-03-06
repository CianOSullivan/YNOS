#ifndef SHELL_H
#define SHELL_H
#include "string.h" // Allows string manipulation
#include "memory.h" // Allows malloc
#include "../cpu/types.h"
#include "../drivers/ports.h"
#include "../cpu/isr.h"
#include "../drivers/screen.h"



#define BACKSPACE 0x0E
#define ENTER 0x1C

static char key_buffer[256];

#define SC_MAX 57



/**
Initialise the keyboard and CPU interrupts (allegedly)
*/
void start_shell();

/**
Parse user input and provide appropriate output

@param input the command the user has input
*/
void user_input(char *input);

/**
Tokenize the input character pointer to an array which can be used to parse

Still need to implement flag support

@param input the character pointer which has been input
@param inputArray the character array which
*/
int argparse(char *input, char* inputArray[]);

#endif
