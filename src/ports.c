#include <stdint.h>

void outb(uint16_t port, uint8_t val) {
	asm volatile("outb %b0, %w1": : "a"(val), "Nd"(port) : "memory");
}

char inb(uint16_t port) {
	char rv;
	asm volatile("inb %1, %0" : "=a"(rv):"dN"(port));
	return rv;
}

void ioWait() {
	outb(0x80, 0);
}

