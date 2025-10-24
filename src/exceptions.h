#pragma once
#include <stdint.h>

typedef struct Registers {
	uint32_t gs, fs, es, ds;
	uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax;
	uint32_t intNo, errCode;
	uint32_t eip, cs, eflags, useresp, ss;
} Registers;
