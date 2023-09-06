#include "../drivers/screen.h"
#include "../cpu/isr.h"

void main(){
    isr_install();
    print("Testing Interupts");
    __asm__ __volatile__("int $2");
    __asm__ __volatile__("int $3");
}