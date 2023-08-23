all: os-image

run:
	qemu-system-x86_64.exe -fda os-image

os-image: boot_sect.bin kernel.bin
	cat $^ > os-image

kernel.bin: kernel_entry.o kernel.o
	ld -o kernel.bin -Ttext 0x1000 $^ --oformat binary

kernel.o: kernel.c
	gcc -ffreestanding -m32 -fno-pie -c $< -o $@

kernel_entry.o : kernel_entry.asm
	nasm $< -f elf -o $0

boot_sect.bin: boot_sect.asm
	nasm $< -f bin -o boot_sect.bin

clean:
	rm -fr *.bin *.o os-image

kernel.dis : kernel.bin
	ndisasm -b 32 $< > $@

