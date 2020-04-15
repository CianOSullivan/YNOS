#ifndef KEYBOARD_H
#define KEYBOARD_H

#include "../cpu/types.h"
#include "ports.h"
#include "../cpu/isr.h"
#include "screen.h"
#include "../kernel/string.h"
#include "../kernel/kernel.h"
#include "../kernel/function.h"
#include "../kernel/shell.h"
void init_keyboard();
#endif // !KEYBOARD_H

