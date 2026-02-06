#include "arch/i386/ports.h"
#include "keyboard.h"
#include <stdbool.h>

char currentKey = 0;

void keyboard_handler() {
    unsigned char scancode = inb(0x60);

    if(scancode & 0x80) {
    } else {
	currentKey = scancode;
    }
    end_of_int();
}

bool is_key_pressed(char key) {
    if(currentKey == key) {
	currentKey = 0;
	return true;
    }
    return false;
}

bool is_key_down(char key) {
    if(currentKey == key) {
	return true;
    }
    return false;
}

char resolve_last_keystroke() {
    char key = currentKey;
    currentKey = 0;
    return key;
}
