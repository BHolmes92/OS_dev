#ifndef IDT_H
#define IDT_H

#include <stdint.h>

#define IDT_ENTRIES 256
#define KERNEL_CS 0x08

//Interupt Gate
typedef struct {
    uint16_t base_low; //Lower 16 bits of address to jmp to
    uint16_t sel;      //Kernel segment selector
    uint8_t  const_zero; //Always zero
    uint8_t  flags;      //Flags
    uint16_t base_hi;    //Upper 16 bits of address to jmp to
}__attribute__((packed)) idt_entry_t;

//Interupt Pointer
typedef struct {
    uint16_t limit;
    uint32_t base;
}__attribute__((packed)) idt_ptr_t;

extern idt_entry_t idt[IDT_ENTRIES];
extern idt_ptr_t idt_reg;

void set_idt_gate(int n, uint32_t handler);
void set_idt();

#endif //IDT_H

