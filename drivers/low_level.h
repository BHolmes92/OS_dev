#ifndef LOW_LEVEL_H
#define LOW_LEVEL_H

unsigned char port_byte_in(unsigned short port);
unsigned char port_byte_out(unsigned short port, unsigned char data);
unsigned char port_word_in(unsigned short port);
unsigned char port_word_out(unsigned short port, unsigned char data);

#endif