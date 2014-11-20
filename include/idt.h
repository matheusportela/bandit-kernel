/**
 * Functions and structures to manage the Interrupt Descriptor Table.
 * 
 * References:
 * http://wiki.osdev.org/Interrupt_Descriptor_Table
 * http://www.osdever.net/bkerndev/Docs/idt.htm
 */

#ifndef _IDT_H_
#define _IDT_H_

#include <stdint.h>
#include <memory.h>

#define IDT_NUM_ENTRIES 256

/**
 * Interrupt Descriptor Table
 * A 6-byte memory location as follows:
 * 0      16       48
 * | size | offset |
 * size: size of the table in bytes subtracted by 1 - minimum 0x100
 *       (0x1000 means 0x200 interrupts).
 * offset: linear address of the table.
 */
struct idt
{
    uint16_t size;
    uint32_t offset;
} __attribute__((packed));

/**
 * Interrupt Descriptor Table entry
 * A 8-byte memory location as follows:
 * 32           16             0
 * |  selector  |   base 0:15  |
 * 64           48      40     32
 * | base 16:31 | flags | zero |
 * base: linear address where the Interrupt Service Routine begins.
 * selector: the segment where the ISR is located in.
 * 
 * flags byte:
 * 8    7     5   4          0
 * | Pr | DPL | S |    GT    |
 * Pr: present bit - 1 for all valid interrupts.
 * DPL: descriptor privilege level - minimum ring level the calling descriptor
 *      must have.
 * S: storage segment - 0 for interrupt gates
 * GT: gate type - possible types:
 *                 32-bit task gate (0x5)
 *                 16-bit interrupt gate (0x6)
 *                 16-bit trap gate (0x7)
 *                 32-bit interrupt gate (0xE)
 *                 32-bit trap gate (0xF)
 */
struct idt_entry
{
    uint16_t base_low;
    uint16_t selector;
    uint8_t zero;
    uint8_t flags;
    uint16_t base_high;
};

/**
 * (asm) Flushes IDT to x86 processor.
 */
extern void idt_flush();

void idt_set_entry(int index, uint32_t base, uint16_t selector, uint8_t flags);
void idt_install();

#endif /* _IDT_H_ */