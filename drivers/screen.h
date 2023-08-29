#ifndef SCREEN_H
#define SCREEN_H

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

//Default Colour
#define WHITE_ON_BLACK 0x0f

//Screen device CRTC Registers
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

//Print character on screen at col row postions
static int print_char(char character, int col, int row, char attribute_byte);

//Get cursor offset for a given col, row pair FROM SCREEN
static int get_screen_offset();

//Set cursor to offset postions TO SCREEN
static void set_screen_offset(int offset);

//Print function
void print_at(char* message, int col, int row);
void print(char* message);

//Clear Screen Function
void clear_screen();

//Get Cursor Memory positon for req coord
static int get_offset(int col, int row);

//Get Row from cursor offset
static int get_offset_row(int offset);

//Get Col from cursor offset
static int get_offset_col(int offset);

//Scroll Screen Text
int text_scroll(int cursor_offset);

#endif