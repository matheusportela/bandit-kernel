#include <gdt.h>

struct gdt gp;
struct gdt_entry gdt[GDT_NUM_ENTRIES];

void gdt_set_entry(int index, uint32_t base, uint32_t limit, uint8_t access,
    uint8_t flags)
{
    gdt[index].base_low = base & 0xFFFF;
    gdt[index].base_middle = (base >> 16) & 0xFF;
    gdt[index].base_high = (base >> 24) & 0xFF;

    gdt[index].limit_low = limit & 0xFFFF;
    gdt[index].limit_high = (limit >> 16) & 0xF;

    gdt[index].access = access;

    gdt[index].flags |= flags & 0xF0;
}

void gdt_install()
{
    /* Configure GDT pointer */
    gp.size = (sizeof(struct gdt_entry) * GDT_NUM_ENTRIES) - 1;
    gp.offset = (uint32_t)&gdt;

    /* NULL descriptor */
    gdt_set_entry(0, 0, 0, 0, 0);

    /*
     * Code segment
     * 
     * access: 0x9A - 10011010
     * Pr: 1 - valid selector
     * Privl: 00 - kernel ring level
     * Always 1 bit
     * Ex: 1 - code selector
     * DC: 0 - executed only by set privilege
     * RW: 1 - writable
     * Ac: 0 - not accessed yet
     * 
     * flag: 0xCF - 11001111
     * Gr: 1 - 4 KiB blocks (page granularity)
     * Sz: 1 - 32-bit protected mode
     */
    gdt_set_entry(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);

    /*
     * Data segment
     * 
     * access: 0x92 - 10010010
     * Pr: 1 - valid selector
     * Privl: 00 - kernel ring level
     * Always 1 bit
     * Ex: 0 - data selector
     * DC: 0 - executed only by set privilege
     * RW: 1 - writable
     * Ac: 0 - not accessed yet
     * 
     * flag: 0xCF - 11001111
     * Gr: 1 - 4 KiB blocks (page granularity)
     * Sz: 1 - 32-bit protected mode
     */
    gdt_set_entry(2, 0, 0xFFFFFFFF, 0x92, 0xCF);

    gdt_flush();
}