#include "../drivers/screen.h"

void main(){
    clear_screen();
    print_at("X", 1, 6);
    print_at("Multiline Spanning Text", 75, 10);
    print_at("This has a line break\nbreak in it", 0, 20);
    print("Another line break");
    print_at("Testing the scrolling functions", 45, 24);
}