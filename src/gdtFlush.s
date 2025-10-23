[BITS 32]
extern gdtp
global gdtFlush
gdtFlush:
    lgdt [gdtp]
    mov eax, cr0
    or al, 1
    mov cr0, eax
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov ss, ax
    jmp 0x08:.flush
.flush:
    ret
