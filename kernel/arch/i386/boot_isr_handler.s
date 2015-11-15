.intel_syntax noprefix

.section .text
.global _isr0
.global _isr1
.global _isr2
.global _isr3
.global _isr4
.global _isr5
.global _isr6
.global _isr7
.global _isr8
.global _isr9
.global _isr10
.global _isr11
.global _isr12
.global _isr13
.global _isr14
.global _isr15
.global _isr16
.global _isr17
.global _isr18
.global _isr19
.global _isr20
.global _isr21
.global _isr22
.global _isr23
.global _isr24
.global _isr25
.global _isr26
.global _isr27
.global _isr28
.global _isr29
.global _isr30
.global _isr31

# we push either 0 if the interrupt doesn't generate an error code or nothing if the error already pushed an error code
# then we push the interrupt number and then call our general isr_handler.
_isr0:
	cli 
	push 0x0000
	push 0x0000
	jmp common_isr_handler
_isr1:
	cli 
	push 0x0000
	push 0x0001
	jmp common_isr_handler
_isr2:
	cli 
	push 0x0000
	push 0x0002
	jmp common_isr_handler
_isr3:
	cli 
	push 0x0000
	push 0x0003
	jmp common_isr_handler
_isr4:
	cli 
	push 0x0000
	push 0x0004
	jmp common_isr_handler
_isr5:
	cli 
	push 0x0000
	push 0x0005
	jmp common_isr_handler
_isr6:
	cli 
	push 0x0000
	push 0x0006
	jmp common_isr_handler
_isr7:
	cli 
	push 0x0000
	push 0x0007
	jmp common_isr_handler
_isr8:
	cli 
	push 0x0008
	jmp common_isr_handler
_isr9:
	cli 
	push 0x0000
	push 0x0009
	jmp common_isr_handler
_isr10:
	cli 
	push 0x000A
	jmp common_isr_handler
_isr11:
	cli 
	push 0x000B
	jmp common_isr_handler
_isr12:
	cli 
	push 0x000C
	jmp common_isr_handler
_isr13:
	cli 
	push 0x000D
	jmp common_isr_handler
_isr14:
	cli 
	push 0x000E
	jmp common_isr_handler
_isr15:
	cli 
	push 0x0000
	push 0x000F
	jmp common_isr_handler
_isr16:
	cli 
	push 0x0000
	push 0x0010
	jmp common_isr_handler
_isr17:
	cli 
	push 0x0000
	push 0x0011
	jmp common_isr_handler
_isr18:
	cli 
	push 0x0000
	push 0x0012
	jmp common_isr_handler
_isr19:
	cli 
	push 0x0000
	push 0x0013
	jmp common_isr_handler
_isr20:
	cli 
	push 0x0000
	push 0x0014
	jmp common_isr_handler
_isr21:
	cli 
	push 0x0000
	push 0x0015
	jmp common_isr_handler
_isr22:
	cli 
	push 0x0000
	push 0x0016
	jmp common_isr_handler
_isr23:
	cli 
	push 0x0000
	push 0x0017
	jmp common_isr_handler
_isr24:
	cli 
	push 0x0000
	push 0x0018
	jmp common_isr_handler
_isr25:
	cli 
	push 0x0000
	push 0x0019
	jmp common_isr_handler
_isr26:
	cli 
	push 0x0000
	push 0x001A
	jmp common_isr_handler
_isr27:
	cli 
	push 0x0000
	push 0x001B
	jmp common_isr_handler
_isr28:
	cli 
	push 0x0000
	push 0x001C
	jmp common_isr_handler
_isr29:
	cli 
	push 0x0000
	push 0x001D
	jmp common_isr_handler
_isr30:
	cli 
	push 0x0000
	push 0x001E
	jmp common_isr_handler
_isr31:
	cli 
	push 0x0000
	push 0x001F
	jmp common_isr_handler

# as part of the interupt routine, eip, cs, eflags, useresp, ss are all pushed onto the stack
# we've already pushed our interrupt number and error code onto the stack
# we then push  EAX, ECX, EDX, EBX, ESP, EBP, ESI, EDI via pusha
# then we push all the segment registers
# this in essence builds the Registers struct in the isr_handler, thereby passing all this state as an object
# to our _handle_fault function
.extern _handle_fault
common_isr_handler:
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
	mov eax, _handle_fault
	call eax
	pop eax
	pop gs
	pop fs
	pop es
	pop ds
	popa
	add esp, 8
	iret

