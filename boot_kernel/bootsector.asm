[org 0x7c00] ;Set base reference

mov bp, 0x9000 ;Set stack
mov sp, bp

mov bx, MSG_REAL_MODE
call print_string

call switch_to_pm

jmp $

%include "../Bootdrive/print_string.asm"
%include "GDT.asm"
%include "print_32.asm"
%include "switch_to_pm.asm"

BEGIN_PM:
    mov ebx, MSG_PROT_MODE
    call print_32;
    jmp $

;GLOBAL VARS
MSG_REAL_MODE db "Started in 16-bit Real Mode", 0
MSG_PROT_MODE db "Sucessfully landed in 32-bit Protected Mode", 0

times 510-($-$$) db 0
dw 0xaa55