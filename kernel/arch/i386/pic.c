#include <kernel/pic.h>
#include <system.h>

void PIC_sendMasterData(unsigned char data){
	outportb(PIC_MASTER_DATA, data);
}

unsigned char PIC_readMasterData() {
	return inportb(PIC_MASTER_DATA);
}

void PIC_sendSlaveData(unsigned char data) {
	outportb(PIC_SLAVE_DATA, data);
}

unsigned char PIC_readSlaveData() {
	return inportb(PIC_SLAVE_DATA);
}

void PIC_sendMasterCommand(unsigned char data){
	outportb(PIC_MASTER_COMMAND, data);
}

unsigned char PIC_readMasterCommand() {
	return inportb(PIC_MASTER_COMMAND);
}

void PIC_sendSlaveCommand(unsigned char data) {
	outportb(PIC_SLAVE_COMMAND, data);
}

unsigned char PIC_readSlaveCommand() {
	return inportb(PIC_SLAVE_COMMAND);
}

void PIC_remap(unsigned char offset1, unsigned char offset2) {
	unsigned char master_mask = PIC_readMasterData();
	unsigned char slave_mask = PIC_readSlaveData();

	PIC_sendMasterCommand(PIC_INIT);
	PIC_sendSlaveCommand(PIC_INIT);
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
		PIC_sendSlaveCommand(PIC_EOI);
	}
	PIC_sendMasterCommand(PIC_EOI);
}