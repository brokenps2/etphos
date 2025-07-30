#include <stdint.h>
#include "vga.h"
#include <stddef.h>

extern char _binary_ter_u12n_psf_start;
extern char _binary_ter_u12n_psf_end;

#define VGA_WIDTH 80
#define VGA_HEIGHT 25
#define VGA_MEMORY 0xB8000

size_t terminalRow;
size_t terminalColumn;
uint8_t terminalColor;
uint16_t* terminalBuffer = (uint16_t*)VGA_MEMORY;

static inline uint8_t vgaEntryColor(enum VGAColor fg, enum VGAColor bg) { return fg | bg << 4; }

static inline uint16_t vgaEntry(unsigned char uc, uint8_t color) { return (uint16_t)uc | (uint16_t)color << 8; }

size_t strlen(const char* str) {
	size_t len = 0;
	while(str[len]) {
		len++;
	}
	return len;
}

void terminalInit() {
	terminalRow = 0;
	terminalColumn = 0;
	terminalColor = vgaEntryColor(VGA_COLOR_WHITE, VGA_COLOR_BLACK);

	for(size_t y = 0; y < VGA_HEIGHT; y++) {
		for(size_t x = 0; x < VGA_WIDTH; x++) {
			const size_t index = y * VGA_HEIGHT + x;
			terminalBuffer[index] = vgaEntry(' ', terminalColor);
		}
	}
}

void terminalSetColor(uint8_t color) {
	terminalColor = color;
}

void terminalPutEntryAt(char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * VGA_WIDTH + x;
	terminalBuffer[index] = vgaEntry(c, color);
}

void terminalPutChar(char c) {
	terminalPutEntryAt(c, terminalColor, terminalColumn, terminalRow);
	if(terminalColumn++ == VGA_WIDTH) {
		terminalColumn = 0;
		if(terminalRow++ == VGA_HEIGHT) {
			terminalRow = 0;
		}
	}
}

void terminalWrite(const char* data, size_t size) {
	for(size_t i = 0; i < size; i++) {
		terminalPutChar(data[i]);
	}
}

void terminalWriteString(const char* data) {
	terminalWrite(data, strlen(data));
}
