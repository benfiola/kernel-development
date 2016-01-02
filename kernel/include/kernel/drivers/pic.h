#ifndef _KERNEL_PIC_H
#define _KERNEL_PIC_H

#define PIC_MASTER	0x20
#define PIC_SLAVE 	0xA0
#define PIC_MASTER_COMMAND PIC_MASTER
#define PIC_MASTER_DATA  PIC_MASTER+1
#define PIC_SLAVE_COMMAND PIC_SLAVE
#define PIC_SLAVE_DATA PIC_SLAVE+1
#define PIC_ICW1_ICW4	0x01
#define PIC_ICW1_SINGLE	0x02
#define PIC_ICW1_INTERVAL4	0x04
#define PIC_ICW1_LEVEL	0x08
#define PIC_ICW1_INIT	0x10
#define PIC_ICW4_8086	0x01
#define PIC_ICW4_AUTO	0x02
#define PIC_ICW4_BUF_SLAVE	0x08
#define PIC_ICW4_BUF_MASTER	0x0C
#define PIC_ICW4_SFN	0x10
#define PIC_EOI 0x20
#define PIC_INIT PIC_ICW1_INIT+PIC_ICW1_ICW4

void PIC_sendMasterCommand(unsigned char data);
unsigned char PIC_readMasterCommand(void);
void PIC_sendMasterData(unsigned char data);
unsigned char PIC_readMasterData(void);
void PIC_sendSlaveCommand(unsigned char data);
unsigned char PIC_readSlaveCommand(void);
void PIC_sendSlaveData(unsigned char data);
unsigned char PIC_readSlaveData(void);
void PIC_remap(unsigned char offset1, unsigned char offset2);
void PIC_eoi(int irq);

#endif