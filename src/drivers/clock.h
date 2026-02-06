#pragma once
#include <stdint.h>

void clock_set_phase(uint32_t hz);
void clock_wait(uint32_t ticks);
void clock_handler();

