#include <memory.h>
#include <gdt.h>
#include <idt.h>
#include <video.h>

/**
 * Run kernel.
 */
void kmain()
{
    /* gdt_install(); */
    
    idt_install();

    vga_init();
    vga_write("Bandit Kernel v0.0.1\n");
    vga_write("Developer: Matheus Vieira Portela\n");
    vga_write("Contact: matheusvportela at gmail dot com\n\n");
    vga_test();
    
    /* Kernel infinite loop */
    while(1) {}
}