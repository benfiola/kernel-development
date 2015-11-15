//code for the interrupt tables.
#include <stdint.h>
#include <kernel/idt.h>

struct IDTEntry{
   uint16_t offset_low; // offset bits 0..15
   uint16_t selector; // a code segment selector in GDT or LDT
   uint8_t zero;      // unused, set to 0
   uint8_t type; // type and attributes, see below
   uint16_t offset_high; // offset bits 16..31
} __attribute__((packed));

struct IDTDescriptor {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)); //__attribute__((packed)) prevents the compiler from optomizing this

struct IDTEntry idt_table[256];
struct IDTDescriptor _idt_pointer;

//extern void isr_wrapper();
extern void _idt_flush();

void addEntry(IDTEntry *entry, uint32_t offset, uint16_t selector, uint8_t type){ 
	entry->offset = (offset & 0xFFFF);
	entry->selector = selector;
	entry->zero = 0x00;
	entry->type = type;
	entry->offset_high = ((offset >> 16) & 0xFFFF);
}

//Called by the kernel to initialize the IDT
void idt_initialize(void){
	int x;
	uint32_t element_size = sizeof(struct IDEntry);
	uint32_t array_size = sizeof(idt_table)/element_size;
	for(x = 0; x < array_size; x++) {

	}
	//_idt_flush();
}

void _interrupt_handler(void){

}