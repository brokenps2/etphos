#include <stdint.h>

void sleepBusy(uint32_t ticks) {
	for(uint32_t i = 0; i < ticks; i++) {
		asm volatile("nop");
	}
}
