#include <stdint.h>
#include "ports.h"

uint32_t clockTicks = 0;

void clock_set_phase(uint32_t hz) {
    int divisor = 119310 / hz;
    outb(0x43, 0x36);
    outb(0x40, divisor & 0xFF);
    outb(0x40, divisor >> 8);
}

void clock_wait(uint32_t ticks) {
    uint32_t eticks;

    eticks = clockTicks + ticks;
    while(clockTicks < eticks);
}

void clock_handler() {
    clockTicks++;
    outb(0x20, 0x20);
}
