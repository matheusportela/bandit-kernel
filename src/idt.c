#include <idt.h>

struct idt idt_ptr;
struct idt_entry idt[IDT_NUM_ENTRIES];

void idt_set_entry(int index, uint32_t base, uint16_t selector, uint8_t flags)
{
    idt[index].base_low = base & 0xFFFF;
    idt[index].base_high = (base >> 16) & 0xFFFF;

    idt[index].selector = selector;

    idt[index].zero = 0;

    idt[index].flags |= flags;
}

void idt_install()
{
    /* Configure IDT pointer */
    idt_ptr.size = (sizeof(struct idt_entry)*IDT_NUM_ENTRIES) - 1;
    idt_ptr.offset = (uint32_t)&idt;

    /* Completely clear IDT */
    memset(idt, 0, sizeof(struct idt_entry)*IDT_NUM_ENTRIES);

    idt_flush();
}