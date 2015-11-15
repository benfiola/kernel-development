#include <stdint.h>
#include <kernel/idt.h>
#include <kernel/isr_handler.h>
#include <stdio.h>

struct Registers
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int interrupt_number, error_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};

char *exception_messages[] = {
	"Division by Zero Exception", 				//0
	"Debug Exception", 							//1
	"Non Maskable Interrupt Exception", 		//2
	"Breakpoint Exception",						//3
	"Into Detected Overflow Exception",			//4
	"Out of Bounds Exception",					//5	
	"Invalid Opcode Exception",					//6
	"No Coprocessor Exception",					//7
	"Double Fault Exception",					//8
	"Coprocessor Segment Overrun Exception",	//9
	"Bad TSS Exception",						//10
	"Segment Not Present Exception",			//11
	"Stack Fault Exception",					//12
	"General Protection Fault Exception",		//13
	"Unknown Interrupt Exception",				//14
	"Coprocessor Fault Exception",				//15
	"Alignment Check Exception",				//16
	"Machine Check Exception",					//17
	"Reserved Exception",						//18
	"Reserved Exception",						//19
	"Reserved Exception",						//20
	"Reserved Exception",						//21
	"Reserved Exception",						//22
	"Reserved Exception",						//23
	"Reserved Exception",						//24
	"Reserved Exception",						//25
	"Reserved Exception",						//26
	"Reserved Exception",						//27
	"Reserved Exception",						//28
	"Reserved Exception",						//29
	"Reserved Exception",						//30
	"Reserved Exception",						//31
};

void idt_isr_handler_install(struct IDTEntry *idt_table) {
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
}

void _handle_fault(struct Registers* regs) {
	printf(exception_messages[regs->interrupt_number]);
}