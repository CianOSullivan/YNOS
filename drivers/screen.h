#ifndef SCREEN_H
#define SCREEN_H

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
// Attribute byte for our default colour scheme
#define WHITE_ON_BLACK 0x0f
// Screen device I/O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5
#include "../cpu/types.h"

void clear_screen();
//int get_screen_offset(int cols, int rows); //his get_offset
int get_offset(int col, int row);
int get_cursor(); // his get_cursor_offset // This is correct
int handle_scrolling(int offset);
void memory_copy(char* source, char* dest, int no_bytes);
void print(char *message);
void print_at(char *message, int col, int row);
int print_char(char c, int col, int row, char attr); // COMPLETE
void set_cursor(int offset);
void print_backspace();

int get_offset_row(int offset);
int get_offset_col(int offset);
#endif