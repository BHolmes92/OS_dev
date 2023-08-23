#Default target
all: kernel.bin

kernel.bin: kernel_entry.o kernel.o
	ld -o kernel.bin -Ttext 0x1000 $^ --oformat binary

kernel.o : kernel.c 
	gcc --freestanding -m32 -fno-pie -c $< -o $@

kernel_entry.o : kernel_entry.asm
	nasm $< -f elf -o $@

