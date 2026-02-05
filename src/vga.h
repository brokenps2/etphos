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

typedef enum VGAColor {
	VGA_COLOR_BLACK = 0,
	VGA_COLOR_BLUE = 1,
	VGA_COLOR_GREEN = 2,
	VGA_COLOR_CYAN = 3,
	VGA_COLOR_RED = 4,
	VGA_COLOR_MAGENTA = 5,
	VGA_COLOR_BROWN = 6,
	VGA_COLOR_LIGHT_GRAY = 7,
	VGA_COLOR_DARK_GRAY = 8,
	VGA_COLOR_LIGHT_BLUE = 9,
	VGA_COLOR_LIGHT_GREEN = 10,
	VGA_COLOR_LIGHT_CYAN = 11,
	VGA_COLOR_LIGHT_RED = 12,
	VGA_COLOR_LIGHT_MAGENTA = 13,
	VGA_COLOR_LIGHT_BROWN = 14,
	VGA_COLOR_WHITE = 15,
} VGAColor;

void term_create(size_t width, size_t height, uint16_t* address, size_t row, size_t column, VGAColor fg, VGAColor bg);
size_t strlen(const char* str);
void term_set_color(VGAColor fg, VGAColor bg);
void term_put_entry_at(char c, uint8_t color, size_t x, size_t y);
void term_put_char(char c);
void term_put_char_before(char c);
void term_write(const char* data, size_t size);
void term_write_string(const char* data);
void term_check_keystroke();
void kprint(const char *str);
int kputs(const char *str);
