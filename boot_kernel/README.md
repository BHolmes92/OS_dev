# Intructions to create
- compile c kernel file ```gcc -ffreestanding -c kernel.c -o kernel.o```
- link c object file ```ld -o kernel.bin -Ttext 0x1000 --oformat binary kernel.o```
- compile bootsector asm file ```nasm boot_sect.asm -f bin -o boot_sect.bin```
- concatinate both files ```cat boot_sect.bin kernel.bin > os-image```
- Run in qemu ```qemu-system-x86_64.exe -fda os-image```

---
# Notes
gcc flag -m32 for 32 bit compilation on 64bit computer  
gcc flag -fno-pie disable position independent executable (solves GDT not found error during linking)

---
# Makefile
- ```$^``` substituted with all target dependancy files
- ```$<``` first dependancy
- ```$@``` target file

clean: commonly used to remove generated files from directory