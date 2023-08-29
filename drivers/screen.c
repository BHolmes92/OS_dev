#include "screen.h"
#include "low_level.h"
#include "../kernel/util.h"

static int print_char(char character, int col, int row, char attribute_byte){
    //Pointer to start of Video Memory
    unsigned char* videomem = (unsigned char*) VIDEO_ADDRESS;
    //Default style if no attribute byte given
    if(!attribute_byte){
        attribute_byte = WHITE_ON_BLACK;
    }

    //Find offset from base ref
    int offset;
    if(col >= 0 && row >= 0){
        offset = get_offset(col, row);          //Find the requested cursor location
    }else{
        offset = get_screen_offset();   //Go from current screen offset (poll screen)
    }

    //If newline is received move cursor to end of current row
    if(character == '\n'){
        row = get_offset_row(offset);
        offset = get_offset(0, row + 1);
    }else{
        videomem[offset] = character;
        videomem[offset + 1] = attribute_byte;
        offset += 2;
    }
    //offset = text_scroll(offset);
    set_screen_offset(offset);
    return offset;
}

static int get_screen_offset(){
    port_byte_out(REG_SCREEN_CTRL, 14); //Cursor location query high byte
    int offset = port_byte_in(REG_SCREEN_DATA) << 8; //Shift to upperhalf
    port_byte_out(REG_SCREEN_CTRL, 15);//Cursor location low byte
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2; //Account for 2bytes per cursor postion due to attributes
}

static void set_screen_offset(int offset){
    offset /= 2; //Reverse calculate on 2 byte per cursor postion
    port_byte_out(REG_SCREEN_CTRL, 14);//High byte
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)offset & 0xff);
}

static int get_offset(int col,int row){
    return 2 * (row * MAX_COLS + col);
}

static int get_offset_row(int offset){
    return offset / (2 * MAX_COLS);
}

static int get_offset_col(int offset){
    return (offset - (get_offset_row(offset)*2*MAX_COLS))/2;
}
//====================================================================================
//Public

//Print a message at specified location
void print_at(char* message, int col, int row){
    //If cursor is not negative update the cursor position
    int offset;
    if(col >= 0 && row >= 0){
        set_screen_offset(get_offset(col, row));
    }

    //Loop through message calling print_char to update video
    int index = 0;
    while(message[index] != 0){
        offset = print_char(message[index++], col, row, WHITE_ON_BLACK);
        row = get_offset_row(offset);
        col = get_offset_col(offset);
    }
}

//Print a message at current location
void print(char* message){
    print_at(message, -1, -1);
}

void clear_screen(){
    //Screen size
    int screen_size = MAX_COLS * MAX_ROWS;
    int i;
    char* screen = (char*)VIDEO_ADDRESS;
    //Loop through video memory and blank 
    for(i = 0; i < screen_size; i++){
        screen[i*2] = ' '; //Move by 2 in video memory due to attribute bits
        screen[i*2 + 1] = WHITE_ON_BLACK; //Clear attribute to defualt
    }
    set_screen_offset(get_offset(0,0));
}

int text_scroll(int cursor_offset){
    //If cursor within screen return cursor
    if(cursor_offset < MAX_ROWS * MAX_COLS *2){
        return cursor_offset;
    }
    //Copy all rows up a row
    int i;
    for(i = 1; i < MAX_ROWS; i++){
        memory_copy((char*)get_screen_offset(0, i) + VIDEO_ADDRESS, (char*)get_screen_offset(0, i-1) + VIDEO_ADDRESS, MAX_COLS *2);
    }
    //Clear the last line for new text
    char* last_line = (char*)get_screen_offset(0, MAX_ROWS - 1) + VIDEO_ADDRESS;
    for(i = 0; i < MAX_COLS *2; i++){
        last_line[i] = 0;
    }
    cursor_offset -= MAX_COLS * 2;

    return cursor_offset;
}

