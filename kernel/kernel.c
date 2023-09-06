#include "../drivers/screen.h"
#include "../cpu/isr.h"

void main(){
    isr_install();
    print("Testing Interupts\n");
    __asm__ __volatile__("int $2");
    __asm__ __volatile__("int $3");
}