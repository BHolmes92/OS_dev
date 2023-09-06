#include "util.h"
#include <stdint.h>

void memory_copy(char* source, char* dest, int no_bytes){
    int i;
    for(i = 0; i<no_bytes; i++){
        *(dest + i) = *(source + i);
    }
}

//Set the destination to value
void memory_set(uint8_t* dest, uint8_t val, uint32_t len){
    uint8_t* temp = (uint8_t*)dest; //Ensure expected pointer size
    while(len > 0){
        *temp = (uint8_t) val;
        temp++;
        len--;
    }
}

void int_to_ascii(int n, char str[]){
    //TODO
}