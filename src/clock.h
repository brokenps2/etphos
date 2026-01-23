#pragma once
#include <stdint.h>

void clockSetPhase(uint32_t hz);
void clockWait(uint32_t ticks);
void clockHandler();
