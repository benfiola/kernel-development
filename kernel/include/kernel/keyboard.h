#ifndef _KERNEL_KEYBOARD_H
#define _KERNEL_KEYBOARD_H

#include <stdbool.h>

void keyboard_handler(struct Registers* regs);
void keyboard_install(void);

#endif