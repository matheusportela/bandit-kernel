#ifndef _IO_H_
#define _IO_H_

#include <stdint.h>

void outb(uint16_t port, uint8_t data);
uint8_t inb(uint16_t port);

#endif /* _IO_H_ */