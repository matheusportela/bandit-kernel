;; boot.asm

bits 32 ; 32-bit processor mode

section .text
    ; GRUB multiboot spec
    ; This is necessary for GRUB to initialize the kernel
    ; (magic + flags + checksum) should be zero
    align 4
    dd 0x1BADB002 ; magic number
    dd 0x00 ; flags (PAGE_ALIGN | MEMORY_INFO | AOUT_KLUDGE)
    dd -(0x1BADB002 + 0x00) ; checksum

global start
extern kmain

start:
    cli
    call kmain
    hlt
    
; Reserve 8 KiB for the stack
; Since the stack grows downward, it's space should be declared before the
; pointer
section .bss
    resb 8192
_sys_stack: