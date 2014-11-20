;; gdt.asm
;;
;; Provides functions for flushing the Global Descriptor Table
;;
;; References:
;; http://wiki.osdev.org/Global_Descriptor_Table
;; http://x86.renejeschke.de/html/file_module_x86_id_156.html


; GDT table pointer
extern gp

; gdt_flush
; Flushes the GDT given a defined table pointer.
global gdt_flush
gdt_flush:
    lgdt [gp]

    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    jmp 0x08:flush2
flush2:
    ret