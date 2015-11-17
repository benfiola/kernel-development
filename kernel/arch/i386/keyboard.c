#include <system.h>
#include <kernel/pic.h>
#include <kernel/irq_handler.h>
#include <kernel/keyboard.h>
#include <stdio.h>
#include <stdbool.h>

struct KeyEvent {
	bool pressed;
	unsigned char keyCode;
	char keyChar;
};

struct KeyEvent keyMap[256] = {
	{.pressed = false, .keyCode=0x00, .keyChar=' '},
};

unsigned char read_status(void) {
	return inportb(0x64);
}

unsigned char read_data(void){
	return inportb(0x60);
}

void keyboard_handler(struct Registers* regs) {
	unsigned char status;
	char keycode;
	status = read_status();
	if(status) {
		keycode = read_data();
		printf("%X ", keycode);
	}
}

void keyboard_install(void){
	//the keyboard is IRQ1
	irq_install_custom_handler(0x01, keyboard_handler);
	outportb(0xF9, 0x00);
}

