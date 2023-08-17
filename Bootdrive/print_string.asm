print_string:
    pusha

    start:
        mov al, [bx]
        cmp al, 0 ;If equal to zero
        je the_end

        mov ah, 0x0e
        int 0x10
        add bx, 1 ;Increment bx pointer by 1
        jmp start

    the_end:
        ;Print new line character
        mov ah, 0x0e
        mov al, 0x0a ;New line
        int 0x10
        mov al, 0x0d ;Carriage return character
        int 0x10
        popa ;Return stack 
        ret
