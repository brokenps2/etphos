#pragma once
#include <stdint.h>

void eaxClockSetPhase(uint32_t hz);
void eaxClockWait(uint32_t ticks);
void eaxClockHandler();
