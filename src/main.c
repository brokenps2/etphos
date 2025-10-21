#include "vga.h"
#include <stdint.h>

Terminal term;

int kernelMain() {
	eaxTermCreate(&term, 80, 25, (uint16_t*)0xB8000, 0, 0, VGA_COLOR_GREEN, VGA_COLOR_BLACK);
	eaxTermWriteString(&term, "fsdfksjfhsdkfj");
	return 0;
}
