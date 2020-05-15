#ifndef SHELL_H
#define SHELL_H
#include "string.h"
#include "../drivers/keyboard.h"
#include "memory.h"

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
void argparse(char *input, char* inputArray[]);

#endif
