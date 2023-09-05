#ifndef UTIL_H
#define UTIL_H

#define low_16(address) (u16)((address) & 0xFFFF) //Take the low 16 bytes of a register
#define high_16(address) (u16)(((address) >> 16) & 0xFFFF) //Take the high 16 bytes of a register

//Copy no_bytes of data FROM source TO dest
void memory_copy(char* source, char* dest, int no_bytes);



#endif 