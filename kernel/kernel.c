#include "../drivers/screen.h"

void main(){
    clear_screen();
    print_at("X", 1, 6);
    print_at("This text should span multiple lines", 75, 10);
    print_at("This should test running off the bottom of screen", 45, 24);
}