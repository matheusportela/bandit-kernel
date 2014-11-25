;; irq.asm
;;
;; Provides Interrupt Request routines for handling hardware interruptions.
;; Each IRQ pushes an return value to the stack and the interrupt number for
;; debugging purposes, as with ISRs.

; C function for interrupt request handling
extern irq_handler

; Implemented IRQs
global irq0
global irq1
global irq2
global irq3
global irq4
global irq5
global irq6
global irq7
global irq8
global irq9
global irq10
global irq11
global irq12
global irq13
global irq14
global irq15

; ISR 32: IRQ 0
irq0:
    cli
    push byte 0 ; dummy error code
    push byte 32
    jmp irq_common_handler

; ISR 33: IRQ 1
irq1:
    cli
    push byte 0 ; dummy error code
    push byte 33
    jmp irq_common_handler

; ISR 34: IRQ 2
irq2:
    cli
    push byte 0 ; dummy error code
    push byte 34
    jmp irq_common_handler

; ISR 35: IRQ 3
irq3:
    cli
    push byte 0 ; dummy error code
    push byte 35
    jmp irq_common_handler

; ISR 36: IRQ 4
irq4:
    cli
    push byte 0 ; dummy error code
    push byte 36
    jmp irq_common_handler

; ISR 37: IRQ 5
irq5:
    cli
    push byte 0 ; dummy error code
    push byte 37
    jmp irq_common_handler

; ISR 38: IRQ 6
irq6:
    cli
    push byte 0 ; dummy error code
    push byte 38
    jmp irq_common_handler

; ISR 39: IRQ 7
irq7:
    cli
    push byte 0 ; dummy error code
    push byte 39
    jmp irq_common_handler

; ISR 40: IRQ 8
irq8:
    cli
    push byte 0 ; dummy error code
    push byte 40
    jmp irq_common_handler

; ISR 41: IRQ 9
irq9:
    cli
    push byte 0 ; dummy error code
    push byte 41
    jmp irq_common_handler

; ISR 42: IRQ 10
irq10:
    cli
    push byte 0 ; dummy error code
    push byte 42
    jmp irq_common_handler

; ISR 43: IRQ 11
irq11:
    cli
    push byte 0 ; dummy error code
    push byte 43
    jmp irq_common_handler

; ISR 44: IRQ 12
irq12:
    cli
    push byte 0 ; dummy error code
    push byte 44
    jmp irq_common_handler

; ISR 45: IRQ 13
irq13:
    cli
    push byte 0 ; dummy error code
    push byte 45
    jmp irq_common_handler

; ISR 46: IRQ 14
irq14:
    cli
    push byte 0 ; dummy error code
    push byte 46
    jmp irq_common_handler

; ISR 47: IRQ 15
irq15:
    cli
    push byte 0 ; dummy error code
    push byte 47
    jmp irq_common_handler

; Common IRQ handler
; Saves the processor state, sets up kernel segments, calls the C IRQ handler
; and restore the stack frame
irq_common_handler:
    ; Save state
    pusha
    push ds
    push es
    push fs
    push gs

    ; Load kernel data segment
    mov ax, 0x10
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax

    ; Push the stack
    mov eax, esp
    push eax

    ; Call C IRQ handler
    mov eax, irq_handler
    call eax ; Special call, preserves eip register

    ; Restore state
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa

    ; Clean the pushed error code and IRQ number from irqX function
    add esp, 8

    ; Pop cs, eip, eflags, ss and esp registers
    iret