lgdt [gdt_descriptor]

mov eax, cr0    ;Read in current cr0
or eax, 0x1     ;Set 1st bit for protected mode
mov cr0, eax    ;Update modified cr0

jmp CODE_SEG:start_protected_mode