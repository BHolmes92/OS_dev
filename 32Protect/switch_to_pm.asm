[bits 16]

switch_to_pm:
    cli ;Turn of CPU interupts during config
    lgdt [gdt_descriptor] ;Load GDT

    mov eax, cr0
    or eax, 0x1
    mov cr0, eax ;Set bit 1 of cr0 for protected mode

    jmp CODE_SEG:init_pm ;far jump to 32 bit code

[bits 32]
init_pm:
    mov ax, DATA_SEG
    mov ds, ax
    mov ss, ax
    mov es, ax
    mov fs, ax
    mov gs, ax  ;Set all segment registers to 32 bit area

    mov ebp, 0x90000
    mov esp, ebp    ;Update stack position

    call BEGIN_PM