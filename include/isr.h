/**
 * Interrupt Service Routines
 * 
 * References:
 * http://www.osdever.net/bkerndev/Docs/isrs.htm
 */

#ifndef _ISR_H_
#define _ISR_H_

#include <stdint.h>
#include <types.h>
#include <idt.h>
#include <video.h>

extern char *isr_exception_message[];

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();

void isr_install();
void isr_handler(struct regs *r);

#endif /* _ISR_H_ */