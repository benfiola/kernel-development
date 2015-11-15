#include <system.h>

void outportb(unsigned short _port, unsigned short _data) {
    __asm__ __volatile__ ("outb %1, %0" : : "dN" (_port), "a" (_data));
}

unsigned short inportb (unsigned short _port)
{
    unsigned short rv;
    __asm__ __volatile__ ("inb %1, %0" : "=a" (rv) : "dN" (_port));
    return rv;
}