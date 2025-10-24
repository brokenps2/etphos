#include "ports.h"
#include "vga.h"

static unsigned char keymapUS[128] = {
    0, 27, '1', '2', '3', '4', '5', '6', '7', '8', '9', '0', '-', '=', '\b'/*backspace*/, 
    '\t', 'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n', 0,
	   'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';', '\'', '`', 0,
	'\\', 'z', 'x', 'c', 'v', 'b', 'n', 'm', ',', '.', '/', 0,
	'*', 0, ' ', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	'-', 0, 0, 0, '+', 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};


void eaxKeyboardHandler() {
    unsigned char scancode = inb(0x60);

    if(scancode & 0x80) {
	//ctrl and alt and stuff
    } else if(scancode == 0x0E) {
	eaxTermPutCharBefore(eaxTermGetMain(), ' ');
    } else {
	eaxTermPutChar(eaxTermGetMain(), keymapUS[scancode]);
    }
}
