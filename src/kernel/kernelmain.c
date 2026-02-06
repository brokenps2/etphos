#include "arch/i386/gdt.h"
#include "arch/i386/idt.h"
#include "arch/i386/irq.h"
#include "drivers/terminal.h"
#include <stdint.h>
#include "stdio.h"

char* words;

int kernelMain() {

	term_create(80, 25, (uint16_t*)0xB8000, 0, 0, VGA_COLOR_LIGHT_GRAY, VGA_COLOR_BLACK);

	gdt_init();
	idt_init();
	irq_install();

	asm volatile("sti");

	while (1) {
		term_check_keystroke();
		asm volatile("hlt");
	}
	return 0;
}
