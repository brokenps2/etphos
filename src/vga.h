#pragma once
#include <stddef.h>
#include <stdint.h>

#define PSF1_FONT_MAGIC 0x0436

typedef struct {
	uint16_t magic;
	uint8_t fontMode;
	uint8_t characterSize;
} PSF1Header;

#define PSF_FONT_MAGIC 0x864ab572

typedef struct {
	uint32_t magic;
	uint32_t version;
	uint32_t headerSize;
	uint32_t flags;
	uint32_t glyphCount;
	uint32_t bytesPerGlyph;
	uint32_t height;
	uint32_t width;
} PSFFont;

typedef struct Terminal {
	size_t width;
	size_t height;
	uint16_t* buffer;
	size_t row;
	size_t column;
	size_t cursorRow;
	size_t cursorColumn;
	uint8_t color;
} Terminal;

typedef enum VGAColor {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GREY = 7,
	VGA_COLOR_DARK_GREY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
} VGAColor;

void eaxTermCreate(Terminal* term, size_t width, size_t height, uint16_t* address, size_t row, size_t column, VGAColor fg, VGAColor bg);
size_t strlen(const char* str);
void eaxTermSetColor(Terminal* term, VGAColor fg, VGAColor bg);
void eaxTermPutEntryAt(Terminal* term, char c, uint8_t color, size_t x, size_t y);
void terminalPutChar(Terminal* term, char c);
void eaxTermWrite(Terminal* term, const char* data, size_t size);
void eaxTermWriteString(Terminal* term, const char* data);
