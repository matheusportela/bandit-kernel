#include <gdt.h>

struct gdt gdt_ptr;
struct gdt_entry gdt[GDT_NUM_ENTRIES];

/**
 * Set parameters for the GDT entry numbered by `index`. It does not check
 * whether `index` is inside the valid range.
 * @param index Number of the GDT entry.
 * @param base Initial memory address for the segment.
 * @param limit Maximum addressable memory for the segment.
 * @param access Access settings, check "gdt.h".
 * @param flags Flags, check "gdt.h" for more information.
 */
void gdt_set_entry(int index, uint32_t base, uint32_t limit, uint8_t access,
    uint8_t flags)
{
    /* Base address */
    gdt[index].base_low = base & 0xFFFF;
    gdt[index].base_middle = (base >> 16) & 0xFF;
    gdt[index].base_high = (base >> 24) & 0xFF;

    /* Limit segment */
    gdt[index].limit_low = limit & 0xFFFF;
    gdt[index].granularity = (limit >> 16) & 0xF;

    /* Flags */
    gdt[index].granularity |= flags & 0xF0;

    /* Access flags */
    gdt[index].access = access;
}

/**
 * Install a configured GDT to the CPU.
 */
void gdt_install()
{
    /* Configure GDT pointer */
    gdt_ptr.size = (sizeof(struct gdt_entry)*GDT_NUM_ENTRIES) - 1;
    gdt_ptr.offset = (uint32_t)&gdt;

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