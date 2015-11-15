#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/tty.h>
#include <kernel/gdt.h>


void kernel_early(void)
{
	terminal_initialize();
	gdt_initialize();
}

void kernel_main(void)
{
	printf("Hello, kernel World!\n");
}
