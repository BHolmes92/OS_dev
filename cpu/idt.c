#include "idt.h"
#include "../kernel/util.h"

void set_idt_gate(int n, uint32_t handler){
    idt[n].base_low = low_16(handler);
    idt[n].sel = KERNEL_CS;
    idt[n].const_zero = 0;
    idt[n].flags = 0x8E;
    idt[n].base_hi = high_16(handler);
}

void set_idt(){
    idt_reg.base = (uint32_t) &idt;
    idt_reg.limit = IDT_ENTRIES * sizeof(idt_entry_t) - 1;
    __asm__ __volatile__("lidtl (%0)" : : "r" (&idt_reg));
}

idt_entry_t idt[IDT_ENTRIES];
idt_ptr_t idt_reg;