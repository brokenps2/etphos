#pragma once
#include <stdint.h>
#include "kernel/exceptions.h"

void irq_set_handler(uint8_t irq, void (*handler)(registers_t* r));
void irq_uninstall_handler(uint8_t irq);
void irq_remap();
void irq_install();

