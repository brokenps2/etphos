#include <stdint.h>
#include "vga.h"
#include "ports.h"
#include <stddef.h>

extern char _binary_ter_u12n_psf_start;
extern char _binary_ter_u12n_psf_end;

static inline uint8_t vgaEntryColor(VGAColor fg, VGAColor bg) { return fg | bg << 4; }

static inline uint16_t vgaEntry(unsigned char uc, uint8_t color) { 
	return (uint16_t)uc | (uint16_t)color << 8;
}

void eaxTermEnableCursor(uint8_t start, uint8_t end) {
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | start);
	
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3D5) & 0xE0) | end);
}

void eaxTermDisableCursor() {
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void eaxTermSetCursorPos(Terminal* term, int row, int column) {
	term->cursorRow = row;
	term->cursorColumn = column;
	uint16_t pos = term->cursorRow * term->width + term->cursorColumn;

	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t)(pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void eaxTermCreate(Terminal* term, size_t width, size_t height, uint16_t* address, size_t row, size_t column, VGAColor fg, VGAColor bg) {
	term->width = width;
	term->height = height;
	term->buffer = address;
	term->row = row;
	term->column = column;
	term->cursorRow = row;
	term->cursorColumn = column;
	term->color = vgaEntryColor(fg, bg);
	for(size_t y = 0; y < term->height; y++) {
		for(size_t x = 0; x < term->width; x++) {
			const size_t index = y * term->height + x;
			term->buffer[index] = vgaEntry(' ', term->color);
		}
	}
}

size_t strlen(const char* str) {
	size_t len = 0;
	while(str[len]) {
		len++;
	}
	return len;
}

void eaxTermSetColor(Terminal* term, VGAColor fg, VGAColor bg) {
	term->color = vgaEntryColor(fg, bg);
}

void eaxTermPutEntryAt(Terminal* term, char c, uint8_t color, size_t x, size_t y) {
	const size_t index = y * term->width + x;
	term->buffer[index] = vgaEntry(c, color);
}

void eaxTermScroll(Terminal* term) {
    for (size_t y = 1; y < term->height; y++) {
        for (size_t x = 0; x < term->width; x++) {
            term->buffer[(y - 1) * term->width + x] =
                term->buffer[y * term->width + x];
        }
    }

    for (size_t x = 0; x < term->width; x++) {
        term->buffer[(term->height - 1) * term->width + x] = vgaEntry(' ', term->color);
    }
}

void eaxTermPutChar(Terminal* term, char c) {
	eaxTermPutEntryAt(term, c, term->color, term->column, term->row);

	if (c == '\n') {
        term->column = 0;
        term->row++;
    } else {
        term->buffer[term->row * term->width + term->column] = vgaEntry(c, term->color);
        if (++term->column >= term->width) {
            term->column = 0;
            term->row++;
        }
    }

    if (term->row >= term->height) {
        eaxTermScroll(term);
        term->row = term->height - 1;
    }

	eaxTermSetCursorPos(term, term->row, term->column);
}

void eaxTermWrite(Terminal* term, const char* data, size_t size) {
	for(size_t i = 0; i < size; i++) {
		eaxTermPutChar(term, data[i]);
	}
}

void eaxTermWriteString(Terminal* term, const char* data) {
	eaxTermWrite(term, data, strlen(data));
}
