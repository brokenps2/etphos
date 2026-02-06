#include <stdint.h>
#include "vga.h"
#include <stddef.h>

uint8_t vga_entry_color(VGAColor fg, VGAColor bg) { return fg | bg << 4; }

uint16_t vga_entry(unsigned char uc, uint8_t color) { 
	return (uint16_t)uc | (uint16_t)color << 8;
}
