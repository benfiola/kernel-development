//code for the interrupt tables.
#include <stdint.h>
#include <kernel/idt.h>
#include <kernel/isr_handler.h>
#include <kernel/irq_handler.h>

struct IDTR {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)); //__attribute__((packed)) prevents the compiler from optomizing this

struct IDTEntry idt_table[256];
struct IDTR _idtr;

//extern void isr_wrapper();
extern void _idt_flush();

void addIDTEntry(struct IDTEntry *entry, uint32_t offset, uint16_t selector, uint8_t type){ 
	entry->offset_low = (offset & 0xFFFF);
	entry->selector = selector;
	entry->zero = 0x00;
	entry->type = ((type<<4) & 0xF0) | 0x1110;
	entry->offset_high = ((offset >> 16) & 0xFFFF);
}

//Called by the kernel to initialize the IDT
void idt_initialize(void){
	uint32_t element_size = sizeof(struct IDTEntry);
	uint32_t array_length = sizeof(idt_table)/element_size;
	idt_isr_handler_install(idt_table);
	idt_irq_handler_install(idt_table);
	_idtr.limit = ((array_length * element_size) - 1);
	_idtr.base = (uint32_t) idt_table;
	_idt_flush();
}