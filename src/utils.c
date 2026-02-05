#include <stdint.h>

void sleep_busy(uint32_t ticks) {
	for(uint32_t i = 0; i < ticks; i++) {
		asm volatile("nop");
	}
}
