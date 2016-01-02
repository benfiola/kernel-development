#ifndef _KERNEL_IDT_H
#define _KERNEL_IDT_H

struct IDTEntry {
   uint16_t offset_low; // offset bits 0..15
   uint16_t selector; // a code segment selector in GDT or LDT
   uint8_t zero;      // unused, set to 0
   uint8_t type; // type and attributes, see below
   uint16_t offset_high; // offset bits 16..31
} __attribute__((packed));

void addIDTEntry(struct IDTEntry *entry, uint32_t offset, uint16_t selector, uint8_t type);
void idt_initialize(void);

#endif