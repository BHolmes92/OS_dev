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
    /* while(len > 0){
        *temp = (uint8_t) val;
        temp++;
        len--;
    } */
    for(; len != 0 ; len--) *temp++ = val;
}

void int_to_ascii(int n, char str[]){
    int index = 0;
    if( n < 0){
        str[index] = '-';
        index++;
    }
    //Loop through integer until zero
    do{
        str[index] = n % 10 + '0'; //Add ascii 0 as offset
        index++;
    }while((n /=10) > 0);
    
    str[index] = '\0';
}