#include "timer.h"
#include "isr.h"
#include "../drivers/screen.h"
#include "../kernel/util.h"
#include "../drivers/low_level.h"

uint32_t tick = 0;

static void timer_callback(registers_t r){
    tick ++;
    print("Tick: ");
    char s[256];
    int_to_ascii(tick, s);
    print("\n");
}

//Set up a timer interupt at a specified frequency **ASSUME** PIC tick is 1.19MHz
void init_timer(uint32_t frequency){
    register_interupt_handler(IRQ0, timer_callback);

    uint32_t divisor = PIC_FRQ / frequency;

    //Send Command to PIC
    port_byte_out(0x43, 0x36); //Repeating mode (cyclical)
    //Send divisor as upper and lower
    uint8_t lower = (uint8_t)(divisor & 0xFF);
    uint8_t upper = (uint8_t)((divisor >> 8) & 0xFF);

    port_byte_out(0x40, lower);
    port_byte_out(0x40, upper);
}
