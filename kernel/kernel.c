#include "../drivers/screen.h"

void main(){
    print("Testing Interupts");
    __asm__ __volatile__("int $2");
    __asm__ __volatile__("int $3");
}