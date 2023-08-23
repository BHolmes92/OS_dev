#include "screen.h"
#include "low_level.h"
#include "../kernel/util.h"

static void print_char(char character, int col, int row, char attribute_byte){
    //Pointer to start of Video Memory
    unsigned char* videomem = (unsigned char*) VIDEO_ADDRESS;
    //Default style if no attribute byte given
    if(!attribute_byte){
        attribute_byte = WHITE_ON_BLACK;
    }

    //Find offset from base ref
    int offset;
    if(col >= 0 && row >= 0){
        offset = get_screen_offset(col, row);
    }else{
        offset = get_cursor();
    }

    //If newline is received move cursor to end of current row
    if(character == '\n'){
        int rows = offset / (2*MAX_COLS);
        offset = get_screen_offset(79, rows);
    }else{
        videomem[offset] = character;
        videomem[offset + 1] = attribute_byte;
    }
    offset += 2; //Move to next cursor postion
    offset = handle_scrolling(offset);
    set_cursor_offset(offset);
}

static int get_screen_offset(int col, int row){
    port_byte_out(REG_SCREEN_CTRL, 14); //Cursor location query high byte
    int offset = port_byte_in(REG_SCREEN_DATA) << 8; //Shift to upperhalf
    port_byte_out(REG_SCREEN_CTRL, 15);//Cursor location low byte
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2; //Account for 2bytes per cursor postion due to attributes
}

static void set_cursor_offset(int offset){
    offset /= 2; //Reverse calculate on 2 byte per cursor postion
    port_byte_out(REG_SCREEN_CTRL, 14);//High byte
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, offset & 0xff);
}
//====================================================================================
//Public
void print_at(char* message, int col, int row){
    //If cursor is not negative update the cursor position
    if(col >= 0 && row >= 0){
        set_cursor_offset(get_screen_offset(col, row));
    }
    int index = 0;
    while(message[index] != 0){
        print_char(message[index++], col, row, WHITE_ON_BLACK);
    }
}

void print(char* message){
    print_at(message, -1, -1);
}

void clear_screen(){

    //Loop through video memory and rest each positons
    for(int row = 0; row < MAX_ROWS; row++){
        for(int col = 0; col < MAX_COLS; col++){
            print_char(' ', col, row, WHITE_ON_BLACK);
        }
    }
    //Set cursor back to 0,0
    set_cursor_offset(get_screen_offset(0,0));
}

int text_scroll(int cursor_offset){
    //If cursor within screen return cursor
    if(cursor_offset < MAX_ROWS * MAX_COLS *2){
        return cursor_offset;
    }
    //Copy all rows up a row
    int i;
    for(i = 1; i < MAX_ROWS; i++){
        memory_copy(get_screen_offset(0, i) + VIDEO_ADDRESS, get_screen_offset(0, i-1) + VIDEO_ADDRESS, MAX_COLS *2);
    }
    //Clear the last line for new text
    char* last_line = get_screen_offset(0, MAX_ROWS - 1) + VIDEO_ADDRESS;
    for(i = 0; i < MAX_COLS *2; i++){
        last_line[i] = 0;
    }
    cursor_offset -= MAX_COLS * 2;

    return cursor_offset;
}