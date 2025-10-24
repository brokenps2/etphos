[BITS 32]
extern idtp
global idtFlush
idtFlush:
    lidt [idtp]
    ret
