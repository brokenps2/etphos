#pragma once
#include <stdint.h>

typedef struct GDTEntry {
	uint16_t limitLow;
	uint16_t baseLow;
	uint8_t baseMiddle;
	uint8_t access;
	uint8_t granularity;
	uint8_t baseHigh;
} __attribute__((packed)) GDTEntry;

typedef struct GDTPtr {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) GDTPtr;

void eaxGDTEncodeEntry(int i, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran);
void eaxGDTInit();
