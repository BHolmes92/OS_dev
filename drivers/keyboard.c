#include "keyboard.h"
#include "../drivers/low_level.h"
#include "../cpu/isr.h"
#include "../drivers/screen.h"
#include "../kernel/util.h"

static void keyboard_callback(registers_t r){
    uint8_t scancode = port_byte_in(0x60);
    char scode[10];
    int_to_ascii(scancode, scode);
    print("Keyboard Scancode Detected:");
    print(scode);
    print("\n");
}

void init_keyboard(){
    register_interupt_handler(IRQ1, keyboard_callback);
}

print_letter(uint8_t code){
    switch(code){
        case(0x01):
            print("Esc");
            break;
        case(0x02):
            print("1");
            break;        
        case(0x03):
            print("2");
            break;
        case(0x04):
            print("3");
            break;
        case(0x05):
            print("4");
            break;        
        case(0x06):
            print("5");
            break;
        case(0x07):
            print("6");
            break;
        case(0x08):
            print("7");
            break;
        case(0x09):
            print("8");
            break;
        case(0x0A):
            print("9");
            break;
        case(0x0B):
            print("0");
            break;
        case(0x0C):
            print("-");
            break;
        case(0x0D):
            print("=");
            break;
        case(0x0E):
            print("Bck");
            break;
        case(0x0F):
            print("Tab");
            break;       
        case(0x10):
            print("Q");
            break;
        case(0x11):
            print("W");
            break;
        case(0x12):
            print("E");
            break;
        case(0x13):
            print("R");
            break;
        case(0x14):
            print("T");
            break;
        case(0x15):
            print("Y");
            break;
        case(0x16):
            print("U");
            break;
        case(0x17):
            print("I");
            break;
        case(0x18):
            print("O");
            break;       
        case(0x19):
            print("P");
            break;
        case(0x1A):
            print("[");
            break;
        case(0x1B):
            print("]");
            break;
        case(0x1C):
            print("Enter");
            break;
        case(0x1D):
            print("LCTRL");
            break;
        case(0x1E):
            print("A");
            break;
        case(0x1F):
            print("S");
            break;
        case(0x20):
            print("D");
            break;
        case(0x21):
            print("F");
            break;
        case(0x22):
            print("G");
            break;
        case(0x23):
            print("H");
            break;
        case(0x24):
            print("J");
            break;
        case(0x25):
            print("K");
            break;
        case(0x26):
            print("L");
            break;
        case(0x27):
            print(";");
            break;
        case(0x28):
            print("'");
            break;
        case(0x29):
            print("`");
            break;
        case(0x2A):
            print("LShift");
            break;        
        case(0x2B):
            print("\\");
            break;       
        case(0x2C):
            print("Z");
            break;
        case(0x2D):
            print("X");
            break;
        case(0x2E):
            print("C");
            break;
        case(0x2F):
            print("V");
            break;
        case(0x30):
            print("B");
            break;
        case(0x31):
            print("N");
            break;  
        case(0x32):
            print("M");
            break;  
        case(0x33):
            print(",");
            break;
        case(0x34):
            print(".");
            break;
        case(0x35):
            print("/");
            break;
        case(0x36):
            print("RShift");
            break;
        case(0x37):
            print("*");
            break;
        case(0x38):
            print("LAlt");
            break;
        case(0x39):
            print("Space");
            break;
        default:
            if(code <= 0xBA){
                print("Key Released: ");
                print_letter(code - 0x80);
            }else{
                print("Unknown Key Event");
            }
    }
}