#include <system.h>
#include <stdint.h>
#include <kernel/idt.h>
#include <kernel/irq_handler.h>
#include <stdio.h>

struct Registers
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int interrupt_number, error_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
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

void irq_remap(void){
	outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);
    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);
    outportb(0x21, 0x0);
    outportb(0xA1, 0x0);
}

void idt_irq_handler_install(struct IDTEntry *idt_table) {
	irq_remap();
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
void _handle_request(struct Registers* regs) {
	printf(request_messages[regs->interrupt_number]);
}