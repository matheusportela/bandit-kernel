#include <idt.h>

struct idt idt_ptr;
struct idt_entry idt[IDT_NUM_ENTRIES];

/**
 * Set parameters for the GDT entry numbered by `index`. It does not check
 * whether `index` is inside the valid range.
 * @param index Number of the GDT entry.
 * @param base Initial memory address for the segment.
 * @param limit Maximum addressable memory for the segment.
 * @param access Access settings, check "gdt.h".
 * @param flags Flags, check "gdt.h".
 */

/**
 * Set parameters for the IDT entry numbered by `index`. It does not check
 * whether `index` is inside the valid range.
 * @param index Number of the IDT entry.
 * @param base Initial memory address for a Interrupt Service Routine.
 * @param selector Segment where the ISR entry is located.
 * @param flags Flags, check "idt.h" for more information.
 */
void idt_set_entry(int index, uint32_t base, uint16_t selector, uint8_t flags)
{
    idt[index].base_low = base & 0xFFFF;
    idt[index].base_high = (base >> 16) & 0xFFFF;

    idt[index].selector = selector;

    idt[index].zero = 0;

    idt[index].flags |= flags;
}

/**
 * Install a configured IDT to the CPU.
 */
void idt_install()
{
    /* Configure IDT pointer */
    idt_ptr.size = (sizeof(struct idt_entry)*IDT_NUM_ENTRIES) - 1;
    idt_ptr.offset = (uint32_t)&idt;

    /* Completely clear IDT */
    memset(idt, 0, sizeof(struct idt_entry)*IDT_NUM_ENTRIES);

    idt_flush();
}