#include <io.h>

/**
 * Write a byte to an output port.
 * @param port Port number.
 * @param data Output byte.
 */
void outportb(uint16_t port, uint8_t data)
{
    __asm__ __volatile__("outb %1, %0" : : "d" (port), "a" (data));
}

/**
 * Receive a byte from an input port.
 * @param port Port number.
 * @return Input byte.
 */
uint8_t inportb(uint16_t port)
{
    uint8_t ret;
    __asm__ __volatile__("inb %1, %0" : "=a" (ret) : "d" (port));
    return ret;
}