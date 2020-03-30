#include "screen.h"
#include "ports.h"


void print_char(char character, int col, int row, char attribute_byte) {
    unsigned char *vidmem = (unsigned char *) VIDEO_ADDRESS;

    if (!attribute_byte) {
        attribute_byte = WHITE_ON_BLACK;
    }

    int offset;

    if (col >= 0 && row >= 0) {
        offset = get_screen_offset(col, row);
    } else {
        offset = get_cursor();
    }

    if (character == '\n') {
        int rows = offset / (2*MAX_COLS);
        offset = get_screen_offset(79, rows);
    } else {
        vidmem[offset] = character;
        vidmem[offset+1] = attribute_byte;
    }

    offset += 2;
    //offset = handle_scrolling(offset);
    set_cursor(offset);
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
    if (col >= 0 && row >= 0){
        set_cursor(get_screen_offset());
    }

    // Loop through message and print it
    int i = 0;
    while (message[i] != 0) {
        print_char(message[i++], col, row, WHITE_ON_BLACK);
    }
}

void print(char *message) {
    print_at(message, -1, -1);
}

void clear_screen() {
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            print_char(' ', col, row, WHITE_ON_BLACK);
        }
    }

    //set_cursor(get_screen_offset(0, 0));
}

int get_screen_offset(int cols, int rows) {
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(get_offset(cols, rows) >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
}

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
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

int get_offset(int col, int row) { return 2 * (row * MAX_COLS + col); }
int handle_scrolling(int offset) { return offset;}
