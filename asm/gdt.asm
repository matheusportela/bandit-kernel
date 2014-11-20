;; gdt.asm
;;
;; Provides functions for flushing the Global Descriptor Table

; GDT table pointer
extern gp

; gdt_flush
; Flushes GDT given a defined table pointer.
global gdt_flush
gdt_flush:
    ; Install GDT in CPU
    lgdt [gp]

    ; Set segment registers to 0x10 - data offset
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Funky way to set CS register to 0x08 - code offset
    jmp 0x08:flush2

flush2:
    ret