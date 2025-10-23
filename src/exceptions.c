#include "kernel.h"
#include "vga.h"

__attribute__((noreturn)) void eaxExceptionHandler();

const char* exceptionMessages[] = {
	"EX0: Division by 0 Exception",
	"EX1: Debug Exception",
	"EX2: Non Maskable Interrupt Exception",
	"EX3: Breakpoint Exception",
	"EX4: Into Detected Overflow Exception",
	"EX5: Out of Bounds Exception",
	"EX6: Invalid Opcode Exception",
	"EX7: No Co-Processor Exception",
	"EX8: Double Fault",
	"EX9: Co-Processor Segment Overrun Exception",
	"EX10: Bad TSS Exception",
	"EX11: Segment Not Present Exception",
	"EX12: Stack Fault",
	"EX13: General Protection Fault",
	"EX14: Page Fault Exception",
	"EX15: Unknown Interrupt Exception",
	"EX16: Co-Processor Fault Exception",
	"EX17: Alignment Check Exception",
	"EX18: Machine Check Exception",
	"EX19-31: Reserved Exception"
};

void eaxExceptionHandler(Registers* r) {

	eaxTermWriteString(getTerm(), "\n\n");
	eaxTermSetColor(getTerm(), VGA_COLOR_LIGHT_RED, VGA_COLOR_BLACK);
	eaxTermWriteString(getTerm(), exceptionMessages[r->intNo]);
	eaxTermWriteString(getTerm(), "\nSystem Halted");
	asm volatile("hlt");
}
