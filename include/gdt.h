/**
 * Functions and structures to manage the Global Descriptor Table.
 * 
 * References:
 * http://wiki.osdev.org/Global_Descriptor_Table
 * http://x86.renejeschke.de/html/file_module_x86_id_156.html
 */

#ifndef _GDT_H_
#define _GDT_H_

#include <stdint.h>

#define GDT_NUM_ENTRIES 3

/**
 * Global Descriptor Table
 * A 6-byte memory location as follows:
 * 0      16       48
 * | size | offset |
 * size: size of the table subtracted by 1.
 * offset: linear address of the table.
 */
struct gdt
{
    uint16_t size;
    uint32_t offset;
} __attribute__((packed));

/**
 * Global Descriptor Table entry
 * A 8-byte memory location as follows:
 * 32                                   16                    0
 * |            base 0:15               |     limit 0:15      |
 * 64             56      52            48       40           32
 * | base 24:31   | flags | limit 16:19 | access | base 16:23 |
 * base: linear address where the segment begins.
 * limit: maximum addressable memory for the segment.
 * 
 * access byte:
 * 8    7       5   4    3    2    1    0
 * | Pr | Privl | 1 | Ex | DC | RW | Ac |
 * Pr: present bit - 1 for all valid selectors.
 * Privl: privilege - selector ring level: 0 is kernel (highest) and 3 is user
 *        applications (lowest).
 * Ex: executable - 0 for data selector, 1 for code selector.
 * DC: direction/conformable -
 *     direction: 0 for selector growing up, 1 for selector growing down for data
 *                selectors.
 *     conformable: 0 for executable only by the privilege level set in Privl, 1
 *                  for executable by equal or lower privilege level for code
 *                  selectors.
 * RW: readable/writable -
 *     readable: readable for code selectors (never writable for code segments).
 *     selectors: writable for data selectors (always readable for data segments).
 * Ac: accessed bit - CPU set to 1 when segment is accessed.
 *
 * flags:
 * 8    7    6   5   4
 * | Gr | Sz | 0 | 0 |
 * Gr: granularity - 0 for limit in 1 byte blocks (byte granularity) and 1 for
 *                   4 KiB blocks (page granularity).
 * Sz: size - 0 for 16-bit protected mode, 1 for 32-bit protected mode.
 */
struct gdt_entry
{
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t base_middle;
    uint8_t access;
    uint8_t limit_high;
    uint8_t flags;
    uint8_t base_high;
};

/**
 * (asm) Flushes GDT to x86 processor.
 */
extern void gdt_flush();

void gdt_set_entry(int index, uint32_t base, uint32_t limit, uint8_t access,
    uint8_t flags);
void gdt_install();

#endif /* _GDT_H_ */