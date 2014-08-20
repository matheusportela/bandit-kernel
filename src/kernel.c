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
    
    /* Kernel infinite loop */
    for(;;)
    {
        busy_wait();
    }
}

void busy_wait()
{
    __asm__ __volatile__("rep; nop" : : : "memory");
}
