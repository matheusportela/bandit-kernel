/**
 * kernel.c
 */

#include <memory.h>
#include <video.h>
#include <limits.h>

void busy_wait();

void kmain()
{
    vga_init();
    vga_test();
    vga_write("\nSpace: Tab:\tNew line:\n\n");
    vga_write("My first kernel\n");
    
    vga_write_char('a');
    /* Kernel infinite loop */
    for(;;)
    {
        /* vga_blink_cursor(); */
        busy_wait();
    }
}

void busy_wait()
{
    __asm__ __volatile__("rep; nop" : : : "memory");
}
