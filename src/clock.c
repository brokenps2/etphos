#include <stdint.h>
#include "ports.h"

uint32_t clockTicks = 0;

void eaxClockSetPhase(uint32_t hz) {
    int divisor = 119310 / hz;
    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, divisor >> 8);
}

void eaxClockWait(uint32_t ticks) {
    uint32_t eticks;

    eticks = clockTicks + ticks;
    while(clockTicks < eticks);
}

void eaxClockHandler() {
    clockTicks++;
    outb(0x20, 0x20);
}
