.intel_syntax noprefix

.section .text
.global _irq0
.global _irq1
.global _irq2
.global _irq3
.global _irq4
.global _irq5
.global _irq6
.global _irq7
.global _irq8
.global _irq9
.global _irq10
.global _irq11
.global _irq12
.global _irq13
.global _irq14
.global _irq15

.section .text
_irq0:
	cli
	push 0x0000
	push 0x0000
	jmp common_irq_handler
_irq1:
	cli
	push 0x0000
	push 0x0001
	jmp common_irq_handler
_irq2:
	cli
	push 0x0000
	push 0x0002
	jmp common_irq_handler
_irq3:
	cli
	push 0x0000
	push 0x0003
	jmp common_irq_handler
_irq4:
	cli
	push 0x0000
	push 0x0004
	jmp common_irq_handler
_irq5:
	cli
	push 0x0000
	push 0x0005
	jmp common_irq_handler
_irq6:
	cli
	push 0x0000
	push 0x0006
	jmp common_irq_handler
_irq7:
	cli
	push 0x0000
	push 0x0007
	jmp common_irq_handler
_irq8:
	cli
	push 0x0000
	push 0x0008
	jmp common_irq_handler
_irq9:
	cli
	push 0x0000
	push 0x0009
	jmp common_irq_handler
_irq10:
	cli
	push 0x0000
	push 0x000A
	jmp common_irq_handler
_irq11:
	cli
	push 0x0000
	push 0x000B
	jmp common_irq_handler
_irq12:
	cli
	push 0x0000
	push 0x000C
	jmp common_irq_handler
_irq13:
	cli
	push 0x0000
	push 0x000D
	jmp common_irq_handler
_irq14:
	cli
	push 0x0000
	push 0x000E
	jmp common_irq_handler
_irq15:
	cli
	push 0x0000
	push 0x000F
	jmp common_irq_handler

#we call the external _handle_request function for our irqs.
.extern _handle_request
common_irq_handler:
	pusha
	push ds
	push es
	push fs
	push gs
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov eax, esp
	push eax
	mov eax, offset _handle_request
	call eax
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8
	iret

.global _test_irq
_test_irq:
	int 0x20
	int 0x21
	int 0x22
	int 0x23
	ret