#pragma once
#include <stdint.h>

typedef struct IDTEntry {
	uint16_t isrLow;
	uint16_t kernelCS;
	uint8_t reserved;
	uint8_t attribs;
	uint16_t isrHigh;
} __attribute__((packed)) IDTEntry;

typedef struct IDTPtr {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) IDTPtr;

void IDTSetEntry(int i, void* isr, uint8_t flags);
void IDTInit();

