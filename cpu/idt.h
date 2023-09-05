#ifndef IDT_H
#define IDT_H

#include <stdint.h>

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

#endif //IDT_H

