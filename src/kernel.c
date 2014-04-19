/**
 * kernel.c
 */

#include "video.h"

void kmain()
{
    vga_init();
    vga_write("My first\tkerne\nl\bs");
}
