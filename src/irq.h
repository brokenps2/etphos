#pragma once
#include <stdint.h>
#include "exceptions.h"

void eaxIRQSetHandler(uint8_t irq, void (*handler)(Registers* r));
void eaxIRQUninstallHandler(uint8_t irq);
void eaxIRQRemap();
void eaxIRQInstall();

