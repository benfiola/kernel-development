//code for the interrupt tables.
#include <stdint.h>
#include <kernel/idt.h>
#include <kernel/isr_handler.h>

struct IDTEntry {
   uint16_t offset_low; // offset bits 0..15
   uint16_t selector; // a code segment selector in GDT or LDT
   uint8_t zero;      // unused, set to 0
   uint8_t type; // type and attributes, see below
   uint16_t offset_high; // offset bits 16..31
} __attribute__((packed));

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
	addIDTEntry(&idt_table[0], (uint32_t) _isr0, 0x08, 0x08);
	addIDTEntry(&idt_table[1], (uint32_t) _isr1, 0x08, 0x08);
	addIDTEntry(&idt_table[2], (uint32_t) _isr2, 0x08, 0x08);
	addIDTEntry(&idt_table[3], (uint32_t) _isr3, 0x08, 0x08);
	addIDTEntry(&idt_table[4], (uint32_t) _isr4, 0x08, 0x08);
	addIDTEntry(&idt_table[5], (uint32_t) _isr5, 0x08, 0x08);
	addIDTEntry(&idt_table[6], (uint32_t) _isr6, 0x08, 0x08);
	addIDTEntry(&idt_table[7], (uint32_t) _isr7, 0x08, 0x08);
	addIDTEntry(&idt_table[8], (uint32_t) _isr8, 0x08, 0x08);
	addIDTEntry(&idt_table[9], (uint32_t) _isr9, 0x08, 0x08);
	addIDTEntry(&idt_table[10], (uint32_t) _isr10, 0x08, 0x08);
	addIDTEntry(&idt_table[11], (uint32_t) _isr11, 0x08, 0x08);
	addIDTEntry(&idt_table[12], (uint32_t) _isr12, 0x08, 0x08);
	addIDTEntry(&idt_table[13], (uint32_t) _isr13, 0x08, 0x08);
	addIDTEntry(&idt_table[14], (uint32_t) _isr14, 0x08, 0x08);
	addIDTEntry(&idt_table[15], (uint32_t) _isr15, 0x08, 0x08);
	addIDTEntry(&idt_table[16], (uint32_t) _isr16, 0x08, 0x08);
	addIDTEntry(&idt_table[17], (uint32_t) _isr17, 0x08, 0x08);
	addIDTEntry(&idt_table[18], (uint32_t) _isr18, 0x08, 0x08);
	addIDTEntry(&idt_table[19], (uint32_t) _isr19, 0x08, 0x08);
	addIDTEntry(&idt_table[20], (uint32_t) _isr20, 0x08, 0x08);
	addIDTEntry(&idt_table[21], (uint32_t) _isr21, 0x08, 0x08);
	addIDTEntry(&idt_table[22], (uint32_t) _isr22, 0x08, 0x08);
	addIDTEntry(&idt_table[23], (uint32_t) _isr23, 0x08, 0x08);
	addIDTEntry(&idt_table[24], (uint32_t) _isr24, 0x08, 0x08);
	addIDTEntry(&idt_table[25], (uint32_t) _isr25, 0x08, 0x08);
	addIDTEntry(&idt_table[26], (uint32_t) _isr26, 0x08, 0x08);
	addIDTEntry(&idt_table[27], (uint32_t) _isr27, 0x08, 0x08);
	addIDTEntry(&idt_table[28], (uint32_t) _isr28, 0x08, 0x08);
	addIDTEntry(&idt_table[29], (uint32_t) _isr29, 0x08, 0x08);
	addIDTEntry(&idt_table[30], (uint32_t) _isr30, 0x08, 0x08);
	addIDTEntry(&idt_table[31], (uint32_t) _isr31, 0x08, 0x08);
	_idtr.limit = ((array_length * element_size) - 1);
	_idtr.base = (uint32_t) idt_table;
	_idt_flush();
}