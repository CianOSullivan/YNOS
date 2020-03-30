#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80
// Attribute byte for our default colour scheme
#define WHITE_ON_BLACK 0x0f
// Screen device I / O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

/* Public kernel API */
void clear_screen();
void print_at(char *message, int col, int row);
void print(char *message);
int handle_scrolling(int offset);

/* Declaration of private functions */
void print_char(char c, int col, int row, char attr); // COMPLETE
int get_cursor(); // his get_cursor_offset
void set_cursor(int offset);
int get_screen_offset(); //his get_offset
int get_offset(int col, int row);
