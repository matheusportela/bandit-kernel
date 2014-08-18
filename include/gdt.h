#ifndef _GDT_H_
#define _GDT_H_

struct gdt_entry_t
{
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_middle;
    unsigned char access;
    unsigned char granularity;
    unsigned char base_high;
} __attribute__((packed));
typedef struct gdt_entry_t gdt_entry_t;

struct gdt_ptr_t
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));
typedef struct gdt_ptr_t gdt_ptr_t;

gdt_entry_t gdt[3];
gdt_ptr_t gp;

extern void gdt_flush(); /* declared at gdt_flush.asm */
void gdt_set_gate(int num, unsigned long base, unsigned long limit,
                  unsigned char access, unsigned char granularity);
void gdt_install();

#endif /* _GDT_H_ */
