#include <isr.h>

char *isr_exception_message[] =
{
    "Division by zero",
    "Debug",
    "Non-maskable interrupt",
    "Breakpoint",
    "Into detected overflow",
    "Out-of-bounds",
    "Invalid opcode",
    "No coprocessor",
    "Double fault",
    "Coprocessor segment overrun",
    "Bad TSS",
    "Segment not present",
    "Stack fault",
    "General protection fault",
    "Page fault",
    "Unknown interrupt",
    "Coprocessor fault",
    "Alignment check",
    "Machine check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};

/**
 * Install Interrupt Service Routines to IDT.
 * All ISRs are in kernel code segment and with 0x8E flag (present entry running
 * in kernel ring).
 */
void isr_install()
{
    idt_set_entry(0, (unsigned)isr0, 0x08, 0x8E);
    idt_set_entry(1, (unsigned)isr1, 0x08, 0x8E);
    idt_set_entry(2, (unsigned)isr2, 0x08, 0x8E);
    idt_set_entry(3, (unsigned)isr3, 0x08, 0x8E);
    idt_set_entry(4, (unsigned)isr4, 0x08, 0x8E);
    idt_set_entry(5, (unsigned)isr5, 0x08, 0x8E);
    idt_set_entry(6, (unsigned)isr6, 0x08, 0x8E);
    idt_set_entry(7, (unsigned)isr7, 0x08, 0x8E);
    idt_set_entry(8, (unsigned)isr8, 0x08, 0x8E);
    idt_set_entry(9, (unsigned)isr9, 0x08, 0x8E);
    idt_set_entry(10, (unsigned)isr10, 0x08, 0x8E);
    idt_set_entry(11, (unsigned)isr11, 0x08, 0x8E);
    idt_set_entry(12, (unsigned)isr12, 0x08, 0x8E);
    idt_set_entry(13, (unsigned)isr13, 0x08, 0x8E);
    idt_set_entry(14, (unsigned)isr14, 0x08, 0x8E);
    idt_set_entry(15, (unsigned)isr15, 0x08, 0x8E);
    idt_set_entry(16, (unsigned)isr16, 0x08, 0x8E);
    idt_set_entry(17, (unsigned)isr17, 0x08, 0x8E);
    idt_set_entry(18, (unsigned)isr18, 0x08, 0x8E);
    idt_set_entry(19, (unsigned)isr19, 0x08, 0x8E);
    idt_set_entry(20, (unsigned)isr20, 0x08, 0x8E);
    idt_set_entry(21, (unsigned)isr21, 0x08, 0x8E);
    idt_set_entry(22, (unsigned)isr22, 0x08, 0x8E);
    idt_set_entry(23, (unsigned)isr23, 0x08, 0x8E);
    idt_set_entry(24, (unsigned)isr24, 0x08, 0x8E);
    idt_set_entry(25, (unsigned)isr25, 0x08, 0x8E);
    idt_set_entry(26, (unsigned)isr26, 0x08, 0x8E);
    idt_set_entry(27, (unsigned)isr27, 0x08, 0x8E);
    idt_set_entry(28, (unsigned)isr28, 0x08, 0x8E);
    idt_set_entry(29, (unsigned)isr29, 0x08, 0x8E);
    idt_set_entry(30, (unsigned)isr30, 0x08, 0x8E);
    idt_set_entry(31, (unsigned)isr31, 0x08, 0x8E);
}

/**
 * Properly handle an ISR.
 * @param r Register values.
 */
void isr_handler(struct regs *r)
{
    if (r->int_no < 32)
    {
        vga_write(isr_exception_message[r->int_no]);
        vga_write(" exception\n");

        while(1) {}
    }
}