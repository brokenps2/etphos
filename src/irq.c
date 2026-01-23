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

void IRQSetHandler(uint8_t irq, void (*handler)(Registers* r)) {
	irqRoutines[irq] = handler;
}

void IRQUninstallHandler(uint8_t irq) {
	irqRoutines[irq] = 0;
}

void IRQRemap() {
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

void IRQInstall() {
	IRQRemap();
	IDTSetEntry(32, irq0, 0x8E);
	IDTSetEntry(33, irq1, 0x8E);
	IDTSetEntry(34, irq2, 0x8E);
	IDTSetEntry(35, irq3, 0x8E);
	IDTSetEntry(36, irq4, 0x8E);
	IDTSetEntry(37, irq5, 0x8E);
	IDTSetEntry(38, irq6, 0x8E);
	IDTSetEntry(39, irq7, 0x8E);
	IDTSetEntry(40, irq8, 0x8E);
	IDTSetEntry(41, irq9, 0x8E);
	IDTSetEntry(42, irq10, 0x8E);
	IDTSetEntry(43, irq11, 0x8E);
	IDTSetEntry(44, irq12, 0x8E);
	IDTSetEntry(45, irq13, 0x8E);
	IDTSetEntry(46, irq14, 0x8E);
	IDTSetEntry(47, irq15, 0x8E);
	IRQSetHandler(0, clockHandler);
	IRQSetHandler(1, keyboardHandler);
	termWriteString("IRQs defined\n");
}

void IRQHandler(Registers* r) {
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
