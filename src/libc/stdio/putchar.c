#include "stdio.h"
#include "drivers/terminal.h"

int putchar(int ic) {
	char c = (char)ic;
	term_write(&c, sizeof(c));
	return ic;
}
