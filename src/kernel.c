#include <memory.h>
#include <gdt.h>
#include <idt.h>
#include <isr.h>
#include <irq.h>
#include <video.h>
#include <test.h>

/**
 * Run kernel.
 */
void kmain()
{
    gdt_install();
    idt_install();
    isr_install();
    irq_install();

    vga_init();
    vga_write("Bandit Kernel v0.0.1\n");
    vga_write("Developer: Matheus Vieira Portela\n");
    vga_write("Contact: matheusvportela at gmail dot com\n\n");
    /*vga_test();*/

    test_division_by_zero_exception();

    /* Kernel infinite loop */
    while(1) {}
}