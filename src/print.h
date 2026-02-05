#include <stdarg.h>
#pragma once

void kvprintf(const char *format, va_list arg);
void kprintf(const char *format, ...);
