;; boot.asm

bits 32 ; protected mode (32-bit processor mode)

section .text
    ; GRUB multiboot spec
    ; This is necessary for GRUB to initialize the kernel
    align 4

    multiboot_header_magic equ 0x1BADB002
    multiboot_header_flags equ 0x00
    multiboot_checksum equ -(multiboot_header_magic + multiboot_header_flags)

    ; GRUB multiboot header, boot signature
    dd multiboot_header_magic
    dd multiboot_header_flags
    dd multiboot_checksum

extern kmain

; Main entry point
global start
start:
    cli
    call kmain
    jmp $
    
; Global Descriptor Table

; Interrupt Service Routines

; Reserve 8 KiB for the stack
; Since the stack grows downward, it's space should be declared before the
; pointer
section .bss
    resb 8192
_sys_stack:
; This line intentionally left blank