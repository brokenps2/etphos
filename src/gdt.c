#include <stdint.h>
#include "gdt.h"

#define GDT_ENTRIES 3

GDTEntry gdt[GDT_ENTRIES];
GDTPtr gdtp;

void eaxGDTEncodeEntry(int i, uint32_t base, uint32_t limit, uint8_t access, uint8_t gran) {
	gdt[i].baseLow = base & 0xFFFF;
	gdt[i].baseMiddle = (base >> 16) & 0xFF;
	gdt[i].baseHigh = (base >> 24) & 0xFF;

	gdt[i].limitLow = limit & 0xFFFF;
	gdt[i].granularity = ((limit >> 16) & 0x0F);

	gdt[i].granularity |= gran & 0xF0;
	gdt[i].access = access;
}

void eaxGDTInit() {
	gdtp.limit = (sizeof(GDTEntry) * GDT_ENTRIES) - 1;
	gdtp.base = (uint32_t)&gdt;

	eaxGDTEncodeEntry(0, 0, 0, 0, 0);
	eaxGDTEncodeEntry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
	eaxGDTEncodeEntry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

	extern void gdtFlush(uint32_t gdtPtr);
	gdtFlush((uint32_t)&gdtp);
}
