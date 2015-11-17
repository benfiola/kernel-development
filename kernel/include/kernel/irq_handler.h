#ifndef _KERNEL_IRQ_HANDLER_H
#define _KERNEL_IRQ_HANDLER_H

struct Registers
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int interrupt_number, error_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};

extern void _irq0(void);
extern void _irq1(void);
extern void _irq2(void);
extern void _irq3(void);
extern void _irq4(void);
extern void _irq5(void);
extern void _irq6(void);
extern void _irq7(void);
extern void _irq8(void);
extern void _irq9(void);
extern void _irq10(void);
extern void _irq11(void);
extern void _irq12(void);
extern void _irq13(void);
extern void _irq14(void);
extern void _irq15(void);

void idt_irq_handler_install(struct IDTEntry *table);
void irq_install_custom_handler(int irq, void (*custom_handler)(struct Registers* regs));
void irq_uninstall_custom_handler(int irq);
#endif