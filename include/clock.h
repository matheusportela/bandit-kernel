#include <irq.h>
#include <io.h>

extern int clock_ticks;

void clock_set_frequency(int freq);
void clock_handler(struct regs *r);
void clock_install();
void clock_wait(int ticks);