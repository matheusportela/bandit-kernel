;; boot.asm

; nasm directive - 32 bit
bits 32
section .text
    ; GRUB multiboot spec
    ; (magic + flags + checksum) should be zero
    align 4
    dd 0x1BADB002 ; magic
    dd 0x00 ; flags
    dd -(0x1BADB002 + 0x00) ; checksum

global start
extern kmain

start:
    cli
    call kmain
    hlt
