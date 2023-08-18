;Boot sector to boot C kernel in 32 Protected mode
[org 0x7c00]
KERNEL_OFFSET equ 0x1000 ;Kernel load point

mov [BOOT_DRIVE], dl ;BIOS boot drive storage
mov bp, 0x9000       ;Set up stack
mov sp, bp

mov bx, MSG_REAL_MODE ;Announce boot sequence start
call print_string
call load_kernel       ;Load kernel
call switch_to_pm       ;Switch to protected mode

jmp $

;Include Statements
%include "../Bootdrive/print_string.asm"
%include "../Bootdrive/disk_load.asm"
%include "../32Protect/GDT.asm"
%include "../32Protect/print_32.asm"
%include "../32Protect/switch_to_pm.asm"

[bits 16]
;load kernel

load_kernel:
    mov bx, MSG_LOAD_KERNEL ;Message identifying kernel load
    call print_string
    mov bx, KERNEL_OFFSET
    mov dh, 15
    mov dl, [BOOT_DRIVE]
    call disk_load

    ret

[bits 32]
;in protected mode

BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print_32
    call KERNEL_OFFSET

    jmp $

;Global Vars
BOOT_DRIVE db 0
MSG_REAL_MODE db "Booting in 16 bit REAL mode", 0
MSG_PROT_MODE db "Booting into 32 bit PROTECTED mode", 0
MSG_LOAD_KERNEL db "Loading kernel to memeory", 0

;Bootsector padding
times 510-($-$$) db 0
dw 0xaa55