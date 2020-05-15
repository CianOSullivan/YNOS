#ifndef KERNEL_H
#define KERNEL_H
#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "string.h"
#include "shell.h"

void some_function();
void kmain();

#endif
