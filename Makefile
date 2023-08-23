C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)
#Create a list of object files by changing the c files in C_SOURCES list
OBJ = ${C_SOURCES:.c=.o}

#all: os-image



os-image: boot/boot_sect.bin kernel.bin
	cat $^ > os-image

kernel.bin: boot/kernel_entry.o ${OBJ}
	ld -o $@ -Ttext 0x1000 -melf_i386 $^ --oformat binary

#Uses patterns to compile object files from corresponding c source files
%.o : %.c ${HEADERS}
	gcc -ffreestanding -m32 -fno-pie -c $< -o $@

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