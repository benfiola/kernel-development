#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

#include <kernel/drivers/tty.h>
#include <kernel/data_tables/gdt.h>
#include <kernel/data_tables/idt.h>
#include <kernel/drivers/keyboard.h>
#include <kernel/drivers/pic.h>

extern void _test_irq();
extern void _test_isr();

void kernel_early(void)
{
	terminal_initialize();
	gdt_initialize();
	idt_initialize();
	keyboard_install();
	
	//mask all IRQs besides keyboard
	PIC_sendMasterData(0xFD);
	PIC_sendSlaveData(0xFF);
}

void kernel_main(void)
{
	asm __volatile__("sti");
	//let's keep the kernel running so we can grab our interrupts.
	for(;;) {
    	asm("hlt");
 	}
}
