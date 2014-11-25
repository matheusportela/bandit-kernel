;; idt.asm
;;
;; Provides Interrupt Service Routines for handling interruptions and exceptions
;; Each ISR pushes an return value to the stack and the interrupt number for
;; debugging purposes.
;; If the exception already returns an error code, the ISR does not need to push
;; another one.

; C function for interrupt handling
extern isr_handler

; Implemented ISRs
global isr0
global isr1
global isr2
global isr3
global isr4
global isr5
global isr6
global isr7
global isr8
global isr9
global isr10
global isr11
global isr12
global isr13
global isr14
global isr15
global isr16
global isr17
global isr18
global isr19
global isr20
global isr21
global isr22
global isr23
global isr24
global isr25
global isr26
global isr27
global isr28
global isr29
global isr30
global isr31

; Division by zero exception
isr0:
    cli
    push byte 0 ; dummy error code
    push byte 0
    jmp isr_common_handler

; Debug exception
isr1:
    cli
    push byte 0 ; dummy error code
    push byte 1
    jmp isr_common_handler

; Non-maskable interrupt exception
isr2:
    cli
    push byte 0 ; dummy error code
    push byte 2
    jmp isr_common_handler

; Breakpoint exception
isr3:
    cli
    push byte 0 ; dummy error code
    push byte 3
    jmp isr_common_handler

; Into detected overflow exception
isr4:
    cli
    push byte 0 ; dummy error code
    push byte 4
    jmp isr_common_handler

; Out-of-bounds exception
isr5:
    cli
    push byte 0 ; dummy error code
    push byte 5
    jmp isr_common_handler

; Invalid opcode exception
isr6:
    cli
    push byte 0 ; dummy error code
    push byte 6
    jmp isr_common_handler

; No-coprocessor exception
isr7:
    cli
    push byte 0 ; dummy error code
    push byte 7
    jmp isr_common_handler

; Double fault exception
; Returns an error code
isr8:
    cli
    push byte 8
    jmp isr_common_handler

; Coprocessor segment overrun exception
isr9:
    cli
    push byte 0 ; dummy error code
    push byte 9
    jmp isr_common_handler

; Bad TSS exception
; Returns an error code
isr10:
    cli
    push byte 10
    jmp isr_common_handler

; Segment not present exception
; Returns an error code
isr11:
    cli
    push byte 11
    jmp isr_common_handler

; Stack fault exception
; Returns an error code
isr12:
    cli
    push byte 12
    jmp isr_common_handler

; General protection fault exception
; Returns an error code
isr13:
    cli
    push byte 13
    jmp isr_common_handler

; Page fault exception
; Returns an error code
isr14:
    cli
    push byte 14
    jmp isr_common_handler

; Unknown interrupt exception
isr15:
    cli
    push byte 0 ; dummy error code
    push byte 15
    jmp isr_common_handler

; Coprocessor fault exception
isr16:
    cli
    push byte 0 ; dummy error code
    push byte 16
    jmp isr_common_handler

; Alignment check exception
isr17:
    cli
    push byte 0 ; dummy error code
    push byte 17
    jmp isr_common_handler

; Machine check exception
isr18:
    cli
    push byte 0 ; dummy error code
    push byte 18
    jmp isr_common_handler

; Reserved exception
isr19:
    cli
    push byte 0 ; dummy error code
    push byte 19
    jmp isr_common_handler

; Reserved exception
isr20:
    cli
    push byte 0 ; dummy error code
    push byte 20
    jmp isr_common_handler

; Reserved exception
isr21:
    cli
    push byte 0 ; dummy error code
    push byte 21
    jmp isr_common_handler

; Reserved exception
isr22:
    cli
    push byte 0 ; dummy error code
    push byte 22
    jmp isr_common_handler

; Reserved exception
isr23:
    cli
    push byte 0 ; dummy error code
    push byte 23
    jmp isr_common_handler

; Reserved exception
isr24:
    cli
    push byte 0 ; dummy error code
    push byte 24
    jmp isr_common_handler

; Reserved exception
isr25:
    cli
    push byte 0 ; dummy error code
    push byte 25
    jmp isr_common_handler

; Reserved exception
isr26:
    cli
    push byte 0 ; dummy error code
    push byte 26
    jmp isr_common_handler

; Reserved exception
isr27:
    cli
    push byte 0 ; dummy error code
    push byte 27
    jmp isr_common_handler

; Reserved exception
isr28:
    cli
    push byte 0 ; dummy error code
    push byte 28
    jmp isr_common_handler

; Reserved exception
isr29:
    cli
    push byte 0 ; dummy error code
    push byte 29
    jmp isr_common_handler

; Reserved exception
isr30:
    cli
    push byte 0 ; dummy error code
    push byte 30
    jmp isr_common_handler

; Reserved exception
isr31:
    cli
    push byte 0 ; dummy error code
    push byte 31
    jmp isr_common_handler

; Common ISR handler
; Saves the processor state, sets up kernel segments, calls the C ISR handler
; and restore the stack frame
isr_common_handler:
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

    ; Call C ISR handler
    mov eax, isr_handler
    call eax ; Special call, preserves eip register

    ; Restore state
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa

    ; Clean the pushed error code and ISR number from isrX function
    add esp, 8

    ; Pop cs, eip, eflags, ss and esp registers
    iret