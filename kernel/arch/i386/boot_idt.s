.intel_syntax noprefix

.section .text
.global _idt_flush
.extern _idtr
_idt_flush:
	lgdt [_idtr]
	ret
