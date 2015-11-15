.intel_syntax noprefix

# Declare constants used for creating a multiboot header.
.set ALIGN,    1<<0             # align loaded modules on page boundaries
.set MEMINFO,  1<<1             # provide memory map
.set FLAGS,    ALIGN | MEMINFO  # this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002       # 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS) # checksum of above, to prove we are multiboot

# Declare a header as in the Multiboot Standard.
.section .multiboot
.align 4
.long MAGIC
.long FLAGS
.long CHECKSUM

# Reserve a stack for the initial thread.
.section .bootstrap_stack, "aw", @nobits
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

# The kernel entry point.
.section .text
.global _start
.type _start, @function
_start:
	mov esp, stack_top

	# Initialize the core kernel before running the global constructors.
	call kernel_early

	# Call the global constructors.
	call _init

	# Transfer control to the main kernel.
	call kernel_main

	# Hang if kernel_main unexpectedly returns.
	cli
.Lhang:
	hlt
	jmp .Lhang

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
.global _gdt_flush
.extern _gdt_pointer
_gdt_flush:
	lgdt [_gdt_pointer]
	mov ax, 0x10
	mov ds, ax
	mov es, ax
	mov fs, ax
	mov gs, ax
	mov ss, ax
	jmp 0x80:_table_flush_return
_table_flush_return:
	ret
.size _start, . - _start
