/**
 * Interrupt Requests routines
 * 
 * References:
 * http://www.osdever.net/bkerndev/Docs/irqs.htm
 */

#ifndef _IRQ_H_
#define _IRQ_H_

#include <io.h>
#include <types.h>
#include <idt.h>

extern void *irq_routines[16];

extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void irq_install_handler(int irq, void (*handler)(struct regs *r));
void irq_uninstall_handler(int irq);
void irq_remap();
void irq_install();
void irq_handler(struct regs *r);

#endif /* _IRQ_H_ */