#pragma once
#include <stdint.h>

typedef struct idtEntry_t {
	uint16_t isrLow;
	uint16_t kernelCS;
	uint8_t reserved;
	uint8_t attribs;
	uint16_t isrHigh;
} __attribute__((packed)) idtEntry_t;

typedef struct idtPtr {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)) idtPtr;

void idt_set_entry(int i, void* isr, uint8_t flags);
void idt_init();

