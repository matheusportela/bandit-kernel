#include <irq.h>

/**
 * Array of function pointers that handle IRQs.
 */
void *irq_routines[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

/**
 * Install a custom handler for a specified IRQ.
 * irq: IRQ number.
 * handler: handler function pointer.
 */
void irq_install_handler(int irq, void (*handler)(struct regs *r))
{
    irq_routines[irq] = handler;
}

/**
 * Remove custom handler for a specified IRQ.
 * irq: IRQ number.
 */
void irq_uninstall_handler(int irq)
{
    irq_routines[irq] = 0;
}

/**
 * IRQs 0 to 7 in protected mode are mapped to IDTs 8 to 15. Thus, it's
 * necessary to send commands to their PICs remapping them from 32 to 47.
 */
void irq_remap()
{
    outportb(0x20, 0x11);
    outportb(0xA0, 0x11);
    outportb(0x21, 0x20);
    outportb(0xA1, 0x28);
    outportb(0x21, 0x04);
    outportb(0xA1, 0x02);
    outportb(0x21, 0x01);
    outportb(0xA1, 0x01);
    outportb(0x21, 0x0);
    outportb(0xA1, 0x0);
}

/**
 * Install Interrupt Request routines to IDT.
 * All IRQs are in kernel code segment and with 0x8E flag (present entry running
 * in kernel ring).
 */
void irq_install()
{
    irq_remap();

    idt_set_entry(32, (unsigned)irq0, 0x08, 0x8E);
    idt_set_entry(33, (unsigned)irq1, 0x08, 0x8E);
    idt_set_entry(34, (unsigned)irq2, 0x08, 0x8E);
    idt_set_entry(35, (unsigned)irq3, 0x08, 0x8E);
    idt_set_entry(36, (unsigned)irq4, 0x08, 0x8E);
    idt_set_entry(37, (unsigned)irq5, 0x08, 0x8E);
    idt_set_entry(38, (unsigned)irq6, 0x08, 0x8E);
    idt_set_entry(39, (unsigned)irq7, 0x08, 0x8E);
    idt_set_entry(40, (unsigned)irq8, 0x08, 0x8E);
    idt_set_entry(41, (unsigned)irq9, 0x08, 0x8E);
    idt_set_entry(42, (unsigned)irq10, 0x08, 0x8E);
    idt_set_entry(43, (unsigned)irq11, 0x08, 0x8E);
    idt_set_entry(44, (unsigned)irq12, 0x08, 0x8E);
    idt_set_entry(45, (unsigned)irq13, 0x08, 0x8E);
    idt_set_entry(46, (unsigned)irq14, 0x08, 0x8E);
    idt_set_entry(47, (unsigned)irq15, 0x08, 0x8E);
}

/**
 * Properly handle an IRQ.
 * @param r Register values.
 */
void irq_handler(struct regs *r)
{
    /* Blank function pointer */
    void (*handler)(struct regs *r);

    /* Apply custom IRQ handler, if any */
    handler = irq_routines[r->int_no - 32];
    if (handler)
        handler(r);

    /*
     * For IRQs 8 to 15 (IDT entries 40 to 47), it's necessary to send an
     * acknowledge signal to the slave PIC.
     */
    if (r->int_no >= 40)
        outportb(0xA0, 0x20);

    /* Always acknowledge the master PIC */
    outportb(0x20, 0x20);
}