#ifndef UTIL_H
#define UTIL_H

#include <stdint.h>

#define low_16(address) (uint16_t)((address) & 0xFFFF) //Take the low 16 bytes of a register
#define high_16(address) (uint16_t)(((address) >> 16) & 0xFFFF) //Take the high 16 bytes of a register

//Copy no_bytes of data FROM source TO dest
void memory_copy(char* source, char* dest, int no_bytes);
void memory_set(uint8_t* dest, uint8_t val, uint32_t len);
void int_to_ascii(int n, char str[]);


#endif 