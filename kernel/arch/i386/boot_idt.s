.intel_syntax noprefix

.section .text
.global _idt_flush
.extern _idtr
.extern _print_addr
_idt_flush:
	lidt [_idtr]
	ret
