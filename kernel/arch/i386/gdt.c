#include <stdint.h>
#include <kernel/gdt.h>

//these are used to point to entries in the GDT.
//the limit has to be between 1-65536 - this is the size of the section
//the base is the address that points to the entry itself
struct GDTDescriptor {
	uint16_t limit;
	uint32_t base;
} __attribute__((packed)); //__attribute__((packed)) prevents the compiler from optomizing this

//each GDTDescriptor points to an GDTEntry, described below.
//we'll use a function to write the fields to this struct
//bytes[0], bytes[1] = limit
//bytes[2], bytes[3], bytes[4] = base
//bytes[5] = access
//bytes[6] = limit[4 bits], then flags [4 bits]
//bytes[7] = base
//
//access byte looks like this
//    7         6          5      4      3                2                1          0
//[Present][Privilege][Privilege][1][Executable][Direction/Conforming][Read/Write][Accessed]
//Present = must be 1 for all selectors
//Privilege = value of 0-3, 0 being kernel and 3 being user applications
//Executable = If a code selector, 1.  If a data selector, 0.
//Direction/Conforming = Direction bit for data selectors - 0 if segment grows up, 1 if segment grows down [offset > limit]
//                       Conforming bit for code selectors, 1 if lower privilege can execute, 0 if not.
//Read/Write = Readable bit for code selectors.  Write is never allowed for code.
//			   Writeable bit for data selectors.  Read is always allowed for data.  
//Accessed bit = CPU will set this, just leave it at 0.
//
//flags bits look like this
//      7        6    5  4
//[Granularity][Size][0][0]
//Granularity bit = defines if limit is 1B blocks (value of zero) or 4kB blocks (value of 1)
//Size bit = 0 means 16 bit protected mode, 1 means 32 bit protected mode.
struct GDTEntry {
	uint8_t bytes[8];
} __attribute__((packed)); //__attribute__((packed)) prevents the compiler from optomizing this

//this just makes it easier for us to define the different entries here, probably a waste of memory.
struct GDTEntryDefinition {
	uint32_t size;
	uint32_t base;
	uint16_t type;
};

struct GDTEntry gdt_table[3];
struct GDTDescriptor _gdt_pointer;

//for convenience, I'll declare these here so that the space is allocated - until we have malloc, we can't depend
//on local struct variables to help us.
struct GDTEntryDefinition NULL_GDT_ENTRY;
struct GDTEntryDefinition CODE_GDT_ENTRY;
struct GDTEntryDefinition DATA_GDT_ENTRY;
struct GDTEntryDefinition TSS_GDT_ENTRY; 

void encodeGdtEntry(struct GDTEntry *target, struct GDTEntryDefinition *entry) {
	target->bytes[0] = (entry->size & 0xFF);
	target->bytes[1] = ((entry->size >> 2) & 0xFF);
	target->bytes[2] = (entry->base & 0xFF);
	target->bytes[3] = ((entry->base >> 2) & 0xFF);
	target->bytes[4] = ((entry->base >> 4) & 0xFF);
	target->bytes[5] = (entry->type & 0xFF);
	target->bytes[6] = ((entry->size >> 4) & 0x0F);
	target->bytes[7] = ((entry->base >> 6) & 0xFF);
}

void prepareEntryDefinition(struct GDTEntryDefinition *entry, uint32_t size, uint32_t base, uint16_t type) {
	entry->size = size;
	entry->base = base;
	entry->type = type;
}

//Called by the kernel to initialize the GDT
//We first prepare 'entry defintions' - these are just simplified versions of GDTEntries - making them easier to create by hand
//Then we convert them to proper GDT entries.
//Finally, we update our memory segments with them
void gdt_initialize(void){
	prepareEntryDefinition(&NULL_GDT_ENTRY, 0, 0, 0);
	prepareEntryDefinition(&CODE_GDT_ENTRY, 0x04000000, 0x03ffffff, 0x009A);
	prepareEntryDefinition(&DATA_GDT_ENTRY, 0x08000000, 0x03ffffff, 0x0092);
	prepareEntryDefinition(&TSS_GDT_ENTRY, 0x0C000000, 0x3ffffff, 0x0089);
	encodeGdtEntry(&gdt_table[0], &NULL_GDT_ENTRY);
	encodeGdtEntry(&gdt_table[1], &CODE_GDT_ENTRY);
	encodeGdtEntry(&gdt_table[2], &DATA_GDT_ENTRY);
	encodeGdtEntry(&gdt_table[3], &TSS_GDT_ENTRY);

	uint32_t element_size = sizeof(struct GDTEntry);
	uint32_t array_length = sizeof(gdt_table)/element_size;
	_gdt_pointer.limit = (array_length * element_size) - 1;
	_gdt_pointer.base = &gdt_table;

}

//This is located in our assembly.
extern void gdt_flush();