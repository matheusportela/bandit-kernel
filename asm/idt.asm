;; idt.asm
;;
;; Provides functions for flushing the Interrupt Descriptor Table

; IDT table pointer
extern idt_ptr

; idt_flush
; Flushes IDT given a defined table pointer.
global idt_flush
idt_flush:
    ; Install IDT in CPU
    lgdt [idt_ptr]
    ret