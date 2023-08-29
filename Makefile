C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)
#Create a list of object files by changing the c files in C_SOURCES list
OBJ = ${C_SOURCES:.c=.o}

#Add Cross-compiler support
CC = /home/ben/opt/cross/bin/i686-elf-gcc
GDB = /home/ben/opt/cross/bin/i686-elf-gdb
CL = /home/ben/opt/cross/bin/i686-elf-ld
#Add dubug sybols
CFLAGS = -g

#all: os-image



os-image: boot/boot_sect.bin kernel.bin
	cat $^ > os-image

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
	rm -fr *.bin *.o os-image
	rm -fr kernel/*.o drivers/*.o boot/*.o

kernel.dis : kernel.bin
	ndisasm -b 32 $< > $@

run:
	qemu-system-x86_64.exe -fda os-image

debug: os-image kernel.elf
	qemu-system-x86_64.exe -s -fda os-image &
	${GDB} -ex "target remote localhost:1234" -ex "symbol-file kernel.elf"

kernel.elf: boot/kernel_entry.o ${OBJ}
	${CL} -o $@ -Ttext 0x1000 $^