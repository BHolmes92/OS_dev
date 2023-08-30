#ifndef TYPES_H
#define TYPES_H

//Typedeffs for more portable code

//Create independent data types
typedef unsigned int u32;
typedef int s32;
typedef unsigned short u16;
typedef short s16;
typedef unsigned char u8;
typedef char s8;

#define low_16(address) (u16)((address) & 0xFFFF) //Take the low 16 bytes of a register
#define high_16(address) (u16)(((address) >> 16) & 0xFFFF) //Take the high 16 bytes of a register

#endif