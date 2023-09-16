#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../cpu/timer.h"

void main(){
    isr_install();
    __asm__ __volatile__("sti");
    init_timer(50);
}