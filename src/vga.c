#include <stdint.h>
#include "vga.h"
#include "ports.h"
#include <stddef.h>

size_t termWidth;
size_t termHeight;
uint16_t* termBuffer;
size_t termRow;
size_t termColumn;
size_t cursorRow;
size_t cursorColumn;
uint8_t termColor;

extern char _binary_ter_u12n_psf_start;
extern char _binary_ter_u12n_psf_end;

static inline uint8_t vgaEntryColor(VGAColor fg, VGAColor bg) { return fg | bg << 4; }

static inline uint16_t vgaEntry(unsigned char uc, uint8_t color) { 
	return (uint16_t)uc | (uint16_t)color << 8;
}

void termEnableCursor(uint8_t start, uint8_t end) {
    outb(0x3D4, 0x0A);
    outb(0x3D5, (inb(0x3D5) & 0xC0) | start);

    outb(0x3D4, 0x0B);
    outb(0x3D5, (inb(0x3D5) & 0xE0) | end);
}

void termDisableCursor() {
    outb(0x3D4, 0x0A);
    outb(0x3D5, 0x20);
}

void termSetCursorPos(int row, int column) {
    cursorRow = row;
    cursorColumn = column;
    uint16_t pos = cursorRow * termWidth + cursorColumn;

    outb(0x3D4, 0x0F);
    outb(0x3D5, (uint8_t)(pos & 0xFF));
    outb(0x3D4, 0x0E);
    outb(0x3D5, (uint8_t)((pos >> 8) & 0xFF));
}

void termCreate(size_t width, size_t height, uint16_t* address, size_t row, size_t column, VGAColor fg, VGAColor bg) {
    termWidth = width;
    termHeight = height;
    termBuffer = address;
    termRow = row;
    termColumn = column;
    cursorRow = row;
    cursorColumn = column;
    termColor = vgaEntryColor(fg, bg);
    for(size_t y = 0; y < termHeight; y++) {
        for(size_t x = 0; x < termWidth; x++) {
            const size_t index = y * termHeight + x;
            termBuffer[index] = vgaEntry(' ', termColor);
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

void termSetColor(VGAColor fg, VGAColor bg) {
    termColor = vgaEntryColor(fg, bg);
}

void termPutEntryAt(char c, uint8_t color, size_t x, size_t y) {
    const size_t index = y * termWidth + x;
    termBuffer[index] = vgaEntry(c, color);
}

void termScroll() {
    for (size_t y = 1; y < termHeight; y++) {
        for (size_t x = 0; x < termWidth; x++) {
            termBuffer[(y - 1) * termWidth + x] = termBuffer[y * termWidth + x];
        }
    }

    for (size_t x = 0; x < termWidth; x++) {
        termBuffer[(termHeight - 1) * termWidth + x] = vgaEntry(' ', termColor);
    }
}

void termPutChar(char c) {
    if (c == '\n') {
        termColumn = 0;
        termRow++;
    } else {
        termPutEntryAt(c, termColor, termColumn, termRow);
        if (++termColumn >= termWidth) {
            termColumn = 0;
            termRow++;
        }
    }

    if (termRow >= termHeight) {
        termScroll();
        termRow = termHeight - 1;
    }

    termSetCursorPos(termRow, termColumn);
}

void termPutCharBefore(char c) {
    termColumn--;
    termSetCursorPos(termColumn, termRow);

    if(c == '\n') {
        termRow--;
        termColumn = termWidth;
        termSetCursorPos(termRow, termColumn);
        return;
    }

    termPutEntryAt(c, termColor, termColumn, termRow);
    if(termColumn == 0) {
	termRow--;
        termColumn = termWidth;
        if(termRow == 0) {
            termRow = termHeight;
        }
    }

}

void termWrite(const char* data, size_t size) {
    for(size_t i = 0; i < size; i++) {
        termPutChar(data[i]);
    }
}

void termWriteString(const char* data) {
    termWrite(data, strlen(data));
}
