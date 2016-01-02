.intel_syntax noprefix

.section .text
.global _gdt_flush
.extern _gdtr
_gdt_flush:
	lgdt [_gdtr]
	jmp 0x08:complete_flush

complete_flush:
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	ret
