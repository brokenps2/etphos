#pragma once
#include <stdint.h>

typedef struct gdtEntry_t {
	uint16_t limitLow;
	uint16_t baseLow;
	uint8_t baseMiddle;
	uint8_t access;
	uint8_t granularity;
	uint8_t baseHigh;
} __attribute__((packed)) gdtEntry_t;

typedef struct gdtPtr {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) gdtPtr;

void gdt_encode_entry(int i, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
void gdt_init();
