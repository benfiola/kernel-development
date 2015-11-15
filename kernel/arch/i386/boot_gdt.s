.intel_syntax noprefix

# we expose the gdt_flush function to our C code at gdt.c
# and the pointer to our gdt_table is exposed to this assembly from gdt.c
# this wasn't clear to me at first.  
# but our GDT table is a collection of 8-byte entries.  
# We have a zeroed out entry as the first entry in our table at 0x00.
# Our second entry is the code segment at 0x08. 
# Our third entry is the data segment at 0x10 (which is 16 bytes away).
# We're basically setting all the registers that live in the data segment to their proper base value.
# Finally, we jump to our code segment to continue execution (note we didn't change the CS register).
# and return back to our C function
.section .gdt
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
