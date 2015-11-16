#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>

extern void _test_irq();
extern void _test_isr();

void kernel_early(void)
{
	terminal_initialize();
	gdt_initialize();
	idt_initialize();
	_test_isr();
}

void kernel_main(void)
{
}
