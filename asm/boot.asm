;; boot.asm

; nasm directive - 32 bit
bits 32
section .text
    ; GRUB multiboot spec
    ; (magic + flags + checksum) should be zero
    align 4
    dd 0x1BADB002 ; magic
    dd 0x00 ; flags (PAGE_ALIGN | MEMORY_INFO | AOUT_KLUDGE)
    dd -(0x1BADB002 + 0x00) ; checksum

global start
extern kmain

start:
    cli
    call kmain
    hlt
    
; reserve 8 KiB for the stack
; since the stack grows downward, it's space should be declared before
; the pointer
;section .bss
;    resb 8192
;_sys_stack:
