#include <clock.h>
#include <video.h>

int clock_ticks = 0;

void clock_set_frequency(int freq)
{
    int divisor = 1193180/freq;

    outportb(0x43, 0x36);
    outportb(0x40, divisor & 0xFF);
    outportb(0x40, divisor >> 8);
}

void clock_handler(struct regs *r)
{
    ++clock_ticks;
    vga_write("clock tick\n");
}

void clock_install()
{
    irq_install_handler(0, clock_handler);
}

void clock_wait(int ticks)
{
    /* What about overflows? */
    int eticks = clock_ticks + ticks;

    while (clock_ticks < eticks) {}
}