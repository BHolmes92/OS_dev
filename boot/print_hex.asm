print_hex:
    pusha
    mov cx, 0
    ;Incoming value in dx

    step:
        cmp cx, 4 ;Loop 4 times ex 0x1234 == 4 char
        je done

        ;Convert current  char to ASCII and print
        mov ax, dx
        and ax, 0x000f ;returns the right bit
        add al, 0x30 ;ACSII to get to number values
        cmp al, 0x39 ;if > ASCII 9 then move to letters
        jle next
        add al, 7; ASCII offset from 9 to A

    next:
        mov bx, HEX_OUT + 5 ;Base pointer plus 5 bits marks the start of the string
        sub bx, cx ;Move pointer as we update cx on each iteration
        mov [bx], al ;take the value at bx to print
        ror dx,4 ;Rotate Right shifts bits right

        add cx, 1
        jmp step

    done:
        mov bx, HEX_OUT
        call print_string
        popa
        ret

;Global Var
    HEX_OUT:
        db '0x0000',0

