/**
 * Provides types used by the system.
 */

#ifndef _TYPES_H_
#define _TYPES_H_

struct regs {
    unsigned int gs, fs, es, ds;
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;
    unsigned int int_no, err_code;
    unsigned int eip, cs, eflags, useresp, ss;
};

#endif /* _TYPES_H_ */