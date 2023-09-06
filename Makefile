C_SOURCES = $(wildcard kernel/*.c drivers/*.c cpu/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h cpu/*.h)
#Create a list of object files by changing the c files in C_SOURCES list
OBJ = ${C_SOURCES:.c=.o cpu/interupt.o}

#Add Cross-compiler support
CC = /home/ben/opt/cross/bin/i686-elf-gcc
GDB = /home/ben/opt/cross/bin/i686-elf-gdb
CL = /home/ben/opt/cross/bin/i686-elf-ld
#Add debug sybols
CFLAGS = -g

#all: os-image



os-image.bin: boot/boot_sect.bin kernel.bin
	cat $^ > os-image.bin

kernel.bin: boot/kernel_entry.o ${OBJ}
	${CL} -o $@ -Ttext 0x1000  $^ --oformat binary

#Uses patterns to compile object files from corresponding c source files
%.o : %.c ${HEADERS}
	${CC} ${CFLAGS} -ffreestanding -c $< -o $@

%.o : %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -o $@

clean:
	rm -fr *.bin *.o os-image *.elf
	rm -fr kernel/*.o drivers/*.o boot/*.o

kernel.dis : kernel.bin
	ndisasm -b 32 $< > $@

run: os-image.bin
	qemu-system-i386 -fda os-image.bin

debug: os-image.bin kernel.elf
	qemu-system-i386 -s -fda os-image.bin &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

kernel.elf: boot/kernel_entry.o ${OBJ}
	${CL} -o $@ -Ttext 0x1000 $^