#include "gdt.h"

void gdt_set_gate(int num, unsigned long base, unsigned long limit,
                  unsigned char access, unsigned char granularity)
{
    /* Setup the GDT base address */
    gdt[num].base_low = base & 0xffff;
    gdt[num].base_middle = (base >> 16) & 0xff;
    gdt[num].base_high = (base >> 24) & 0xff;
    
    /* Setup descriptor limits */
    gdt[num].limit_low = limit & 0xffff;
    gdt[num].granularity = (limit >> 16) & 0x0f;
    
    /* Setup granularity and access flags */
    gdt[num].granularity |= granularity & 0x0f;
    gdt[num].access = access;
}

void gdt_install()
{
    /* Setup GDT pointer and limit */
    gp.limit = (sizeof(gdt_entry_t)*3) - 1;
    gp.base = (unsigned int)&gdt;
    
    /* NULL descriptor */
    gdt_set_gate(0, 0, 0, 0, 0);
    
    /* Code segment */
    gdt_set_gate(1, 0, 0xffffffff, 0x9a, 0xcf);
    
    /* Data segment */
    gdt_set_gate(2, 0, 0xffffffff, 0x92, 0xcf);
    
    gdt_flush();
}
