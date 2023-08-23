;Load DH sector to ES

disk_load:
    push dx

    mov ah, 0x02
    mov al, dh
    mov ch, 0x00
    mov dh, 0x00
    mov cl, 0x02

    int 0x13

    jc disk_error ;Jump if Carry Flag

    pop dx
    cmp dh, al ;Check if all requested sectors read
    jne disk_error
    ret

    disk_error:
        mov bx, DISK_ERROR_MSG
        call print_string
        jmp $

    DISK_ERROR_MSG db "Disk Read Error", 0