#include <stdint.h>
#include "exceptions.h"
#include "idt.h"
#include "keyboard.h"
#include "ports.h"
#include "clock.h"
#include "vga.h"

void* irqRoutines[16] = {
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0,
	0, 0, 0, 0
};

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void eaxIRQSetHandler(uint8_t irq, void (*handler)(Registers* r)) {
	irqRoutines[irq] = handler;
}

void eaxIRQUninstallHandler(uint8_t irq) {
	irqRoutines[irq] = 0;
}

void eaxIRQRemap() {
	outb(0x20, 0x11);
	ioWait();
	outb(0xA0, 0x11);
	ioWait();
	outb(0x21, 0x20);
	ioWait();
	outb(0xA1, 0x28);
	ioWait();
	outb(0x21, 0x04);
	ioWait();
	outb(0xA1, 0x02);
	ioWait();
	outb(0x21, 0x01);
	ioWait();
	outb(0xA1, 0x01);
	ioWait();
	outb(0x21, 0x00);
	ioWait();
	outb(0xA1, 0x00);
	ioWait();
}

void eaxIRQInstall() {
	eaxIRQRemap();
	eaxIDTSetEntry(32, irq0, 0x8E);
	eaxIDTSetEntry(33, irq1, 0x8E);
	eaxIDTSetEntry(34, irq2, 0x8E);
	eaxIDTSetEntry(35, irq3, 0x8E);
	eaxIDTSetEntry(36, irq4, 0x8E);
	eaxIDTSetEntry(37, irq5, 0x8E);
	eaxIDTSetEntry(38, irq6, 0x8E);
	eaxIDTSetEntry(39, irq7, 0x8E);
	eaxIDTSetEntry(40, irq8, 0x8E);
	eaxIDTSetEntry(41, irq9, 0x8E);
	eaxIDTSetEntry(42, irq10, 0x8E);
	eaxIDTSetEntry(43, irq11, 0x8E);
	eaxIDTSetEntry(44, irq12, 0x8E);
	eaxIDTSetEntry(45, irq13, 0x8E);
	eaxIDTSetEntry(46, irq14, 0x8E);
	eaxIDTSetEntry(47, irq15, 0x8E);
	eaxIRQSetHandler(0, eaxClockHandler);
	eaxIRQSetHandler(1, eaxKeyboardHandler);
	eaxTermWriteString(eaxTermGetMain(), "- IRQs defined\n");
}

void eaxIRQHandler(Registers* r) {
	void (*handler)(Registers* r);

	handler = irqRoutines[r->intNo - 32];
	if(handler) {
		handler(r);
	}

	if(r->intNo >= 40) {
		outb(0xA0, 0x20);
	}

	outb(0x20, 0x20);
}
