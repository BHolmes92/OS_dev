#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"

void main(){
    isr_install();
    clear_screen();
    __asm__ __volatile__("int $2");
    __asm__ __volatile__("int $3");
}