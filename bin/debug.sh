qemu-system-i386 -s -S -cdrom eax2.iso &
gdb eax2 -ex 'target remote :1234'
