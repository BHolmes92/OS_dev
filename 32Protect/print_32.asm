[bits 32]
;Define constants
VIDEO_MEMORY equ 0xb8000
WHITE_ON_BLACK equ 0x0f

;prints a null terminated string pointed to by edx
print_32:
    pusha
    mov edx, VIDEO_MEMORY

print_string_loop:
    mov al, [ebx]
    mov ah, WHITE_ON_BLACK ;Attributes stored in upper half of ax

    cmp al,0
    je done ;Check for 0 indicating end of string
    
    mov [edx], ax ;Store current character and attributes to edx in Video memory
    add ebx, 1 ;Move to next character in string
    add edx, 2 ;Video memory is 2 bits per char, move to next char in memory

    jmp print_string_loop

done:
    popa
    ret