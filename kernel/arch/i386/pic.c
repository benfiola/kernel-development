#include <kernel/pic.h>
#include <system.h>

void PIC_sendMasterData(unsigned char data){
	outportb(PIC_MASTER_WRITE, data);
}

unsigned char PIC_readMasterData() {
	return inportb(PIC_MASTER_READ);
}

void PIC_sendSlaveData(unsigned char data) {
	outportb(PIC_SLAVE_WRITE, data);
}

unsigned char PIC_readSlaveData() {
	return inportb(PIC_SLAVE_READ);
}

void PIC_remap(unsigned char offset1, unsigned char offset2) {
	unsigned char master_mask = PIC_readMasterData();
	unsigned char slave_mask = PIC_readSlaveData();

	PIC_sendMasterData(PIC_INIT);
	PIC_sendSlaveData(PIC_INIT);
	PIC_sendMasterData(offset1);
	PIC_sendSlaveData(offset2);
	PIC_sendMasterData(0x04); // tell master that the slave is at IRQ2 - 00000100 (each IRQ port is a bit in this number)
	PIC_sendSlaveData(0x02);  // tell slave its cascade identity - the 2 in IRQ2
	PIC_sendMasterData(PIC_ICW4_8086);
	PIC_sendSlaveData(PIC_ICW4_8086);
	PIC_sendMasterData(master_mask);
	PIC_sendSlaveData(slave_mask);
}

void PIC_eoi(int irq) {
	if(irq >= 8) {
		PIC_sendSlaveData(PIC_EOI);
	}
	PIC_sendMasterData(PIC_EOI);
}