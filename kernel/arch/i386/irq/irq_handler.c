#include <system.h>
#include <stdint.h>
#include <kernel/data_tables/idt.h>
#include <kernel/irq/irq_handler.h>
#include <stdio.h>
#include <kernel/drivers/pic.h>

void* idt_custom_handlers[16] = {
	0,							//0
	0,							//1
	0,							//2
	0,							//3
	0,							//4
	0,							//5
	0,							//6
	0,							//7
	0,							//8
	0,							//9
	0,							//10
	0,							//11
	0,							//12
	0,							//13
	0,							//14
	0							//15
};

char *request_messages[] = {
	"IRQ 0",							//0
	"IRQ 1",							//1
	"IRQ 2",							//2
	"IRQ 3",							//3
	"IRQ 4",							//4
	"IRQ 5",							//5
	"IRQ 6",							//6
	"IRQ 7",							//7
	"IRQ 8",							//8
	"IRQ 9",							//9
	"IRQ 10",							//10
	"IRQ 11",							//11
	"IRQ 12",							//12
	"IRQ 13",							//13
	"IRQ 14",							//14
	"IRQ 15"							//15
};

void idt_irq_handler_install(struct IDTEntry *idt_table) {
	PIC_remap(0x20, 0x28);
	addIDTEntry(&idt_table[32], (uint32_t) _irq0, 0x08, 0x08);
	addIDTEntry(&idt_table[33], (uint32_t) _irq1, 0x08, 0x08);
	addIDTEntry(&idt_table[34], (uint32_t) _irq2, 0x08, 0x08);
	addIDTEntry(&idt_table[35], (uint32_t) _irq3, 0x08, 0x08);
	addIDTEntry(&idt_table[36], (uint32_t) _irq4, 0x08, 0x08);
	addIDTEntry(&idt_table[37], (uint32_t) _irq5, 0x08, 0x08);
	addIDTEntry(&idt_table[38], (uint32_t) _irq6, 0x08, 0x08);
	addIDTEntry(&idt_table[39], (uint32_t) _irq7, 0x08, 0x08);
	addIDTEntry(&idt_table[40], (uint32_t) _irq8, 0x08, 0x08);
	addIDTEntry(&idt_table[41], (uint32_t) _irq9, 0x08, 0x08);
	addIDTEntry(&idt_table[42], (uint32_t) _irq10, 0x08, 0x08);
	addIDTEntry(&idt_table[43], (uint32_t) _irq11, 0x08, 0x08);
	addIDTEntry(&idt_table[44], (uint32_t) _irq12, 0x08, 0x08);
	addIDTEntry(&idt_table[45], (uint32_t) _irq13, 0x08, 0x08);
	addIDTEntry(&idt_table[46], (uint32_t) _irq14, 0x08, 0x08);
	addIDTEntry(&idt_table[47], (uint32_t) _irq15, 0x08, 0x08);
}

void irq_install_custom_handler(int irq, void (*custom_handler)(struct Registers *regs)) {
	idt_custom_handlers[irq] = custom_handler;
}

void irq_uninstall_custom_handler(int irq) {
	idt_custom_handlers[irq] = 0;
}

void _handle_request(struct Registers* regs) {
	void (*custom_handler)(struct Registers *regs);
	int irq_number = regs->interrupt_number - 32;
	custom_handler = idt_custom_handlers[irq_number];
	if(custom_handler) {
		custom_handler(regs);
	} else {
		printf("%s\n", request_messages[irq_number]);
	}
	PIC_eoi(irq_number);
}