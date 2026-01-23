#pragma once
#include <stdint.h>
#include "exceptions.h"

void IRQSetHandler(uint8_t irq, void (*handler)(Registers* r));
void IRQUninstallHandler(uint8_t irq);
void IRQRemap();
void IRQInstall();

