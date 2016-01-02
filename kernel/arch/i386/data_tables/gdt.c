#include <stdint.h>
#include <kernel/data_tables/gdt.h>

struct GDTEntry {
	uint16_t limit_low;
	uint16_t base_low;
	uint8_t base_middle;
	uint8_t access;
	uint8_t limit_high_and_flags;
	uint8_t base_high;

} __attribute__((packed)); //__attribute__((packed)) prevents the compiler from optomizing this

struct GDTR {
	uint16_t limit;
	uint32_t base;
}__attribute__((packed));

struct GDTEntry gdt_table[3];
struct GDTR _gdtr;

//We're going to make a call to our boot_gdt assembly code via this extern function.
extern void _gdt_flush();

void addGDTEntry(struct GDTEntry *entry, uint32_t base, uint32_t limit, uint8_t access, uint8_t flags) {
	entry->base_low = base & 0xFFFF;
	entry->limit_low = limit & 0xFFFF;
	entry->base_middle = (base >> 16) & 0xFF;
	entry->access = access;
	entry->limit_high_and_flags =  ((limit >> 16) & 0x0F) | (flags << 4 & 0xF0);
	entry->base_high = (base >> 24) & 0xFF;
}

//Called by the kernel to initialize the GDT
//We first prepare 'entry defintions' - these are just simplified versions of GDTEntries - making them easier to create by hand
//Then we convert them to proper GDT entries.
//Finally, we update our memory segments with them
void gdt_initialize(void){
	addGDTEntry(&gdt_table[0], 0, 0, 0, 0);
	addGDTEntry(&gdt_table[1], 0, 0xFFFFFFFF, 0x9A, 0xFF);
	addGDTEntry(&gdt_table[2], 0, 0xFFFFFFFF, 0x92, 0xFF);
	uint32_t element_size = sizeof(struct GDTEntry);
	uint32_t array_length = sizeof(gdt_table)/element_size;
	_gdtr.limit = ((array_length * element_size) - 1);
	_gdtr.base = (uint32_t) gdt_table;
	_gdt_flush();
}