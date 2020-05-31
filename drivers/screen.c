#include "screen.h"
#include "ports.h"


int print_char(char character, int col, int row, char attribute_byte) {
    u8 *vidmem = (u8*) VIDEO_ADDRESS;

    if (!attribute_byte) {
        attribute_byte = WHITE_ON_BLACK;
    }

    if (colour) {
        attribute_byte = colour;
    }

    int offset;

    if (col >= 0 && row >= 0) {
        offset = get_offset(col, row);
    } else {
        offset = get_cursor(); // This works
    }

    if (character == '\n') {
        row = get_offset_row(offset);
        offset = get_offset(0, row+1); // This works
    } else if (character == 0x08) { /* Backspace */
        vidmem[offset] = ' ';
        vidmem[offset+1] = attribute_byte;
    } else {
        vidmem[offset] = character;
        vidmem[offset+1] = attribute_byte;
        offset += 2;
    }

    offset = handle_scrolling(offset);

    set_cursor(offset);
    return offset;
}

/**
Convert integers to characters in order to print them
 */
char *tochar(int i, char *p)
{
    if (i / 10 == 0) {
        // No more digits
        *p++ = i + '0';
        *p = '\0';
        return p;
    }

    p = tochar(i / 10, p);
    *p++ = i % 10 + '0';
    *p = '\0';
    return p;
}


/**********************************************************
 * Public Kernel API functions                            *
 **********************************************************/

/**
 * Print a message on the specified location
 * If col, row, are negative, we will use the current offset
 */
void print_at(char *message, int col, int row) {
    // Set cursor if col/row are not negative
    int offset;
    if (col >= 0 && row >= 0)
        offset = get_offset(col, row);
    else {
        offset = get_cursor();
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }

    // Loop through message and print it
    int i = 0;
    while (message[i] != 0) {
        offset = print_char(message[i++], col, row, WHITE_ON_BLACK);
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}

void print(char *message) {
    print_at(message, -1, -1);
}

void print_int(char *message, int n) {
    char buffer[100];
    print_at(message, -1, -1);
    tochar(n, buffer);
    print_at(buffer, -1, -1);
}

void print_backspace() {
    int offset = get_cursor()-2;
    int row = get_offset_row(offset);
    int col = get_offset_col(offset);
    print_char(0x08, col, row, WHITE_ON_BLACK);
    set_cursor(offset);
}

void clear_screen() {
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            print_char(' ', col, row, WHITE_ON_BLACK);
        }
    }
    set_cursor(get_offset(0, 0));
}

/******** END PUBLIC FUNCTIONS *********/

int get_cursor() {
    /* Use the VGA ports to get the current cursor position
     * 1. Ask for high byte of the cursor offset (data 14)
     * 2. Ask for low byte (data 15)
     */
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8; /* High byte: << 8 */
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2; /* Position * size of character cell */
}

void set_cursor(int offset) {
    /* Similar to get_cursor_offset, but instead of reading we write data */
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (u8)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (u8)(offset & 0xff));
}

void memory_copy(char* source, char* dest, int no_bytes) {
    int i;
    for (i = 0; i < no_bytes; i++) {
        *(dest + i) = *(source + i);
    }
}

int get_offset(int col, int row) { return 2 * (row * MAX_COLS + col); }
int handle_scrolling(int offset) {
    if (offset < MAX_ROWS * MAX_COLS * 2) {
        set_cursor(offset);
        return offset;
    }

    /* Check if the offset is over screen size and scroll */
    if (offset >= MAX_ROWS * MAX_COLS * 2) {
        int i;
        for (i = 1; i < MAX_ROWS; i++)
            memory_copy((u8*)get_offset(0, i) + VIDEO_ADDRESS,
                        (u8*)get_offset(0, i-1) + VIDEO_ADDRESS,
                        MAX_COLS * 2);

        /* Blank last line */
        char *last_line = get_offset(0, MAX_ROWS-1) + (u8*) VIDEO_ADDRESS;

        for (i = 0; i < MAX_COLS * 2; i++) last_line[i] = 0;

        offset -= 2 * MAX_COLS;
    }
    return offset;
}
int get_offset_row(int offset) { return offset / (2 * MAX_COLS); }
int get_offset_col(int offset) { return (offset - (get_offset_row(offset)*2*MAX_COLS))/2; }
