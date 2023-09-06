[extern isr_handler]

;Common Interupt Code
isr_common_stub:
    ;Save State
    pusha
    mov ax, ds;
    push eax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    call isr_handler

    ;Restore Saved State
    pop eax
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    popa
    add esp, 8
    sti
    iret


;Common ISR NASM macro generation
%macro ISR_NOERRCODE 1
    [GLOBAL isr%1] //Will replace with first parameter etc isr0
    isr%1:         //Same as above
        cli
        push byte 0
        push byte %1
        jmp isr_common_stub
%endmacro

%macro ISR_ERRCODE 1
    [GLOBAL isr%1]
    isr%1:
        cli
        push byte %1
        jmp isr_common_stub
%endmacro
