bits 32

section .multiboot               ;according to multiboot spec
        dd 0x1BADB002            ;set magic number for
                                 ;bootloader
        dd 0x0                   ;set flags
        dd - (0x1BADB002 + 0x0)  ;set checksum

section .text
global start
global setGdt
extern main                      ;defined in the C file

setGdt:
        mov eax, [esp + 4]
        lgdt [eax]
        ret

start:
        cli                      ;block interrupts
        mov esp, stack_space     ;set stack pointer
        call main
        hlt                      ;halt the CPU

; ###################### IDT PART ###########################

; IDT Load

global _idt_load
extern _idtp
_idt_load:
    lidt [_idtp]
    ret

; ISRs (Interruption Service Routines)

global _isr0

_isr0:
    cli
    push byte 0 ; Dummy error code
    push byte 0 ; ISR number
    jmp isr_common_stub

; Fault handler is the general function that will hold CPU errors
extern _fault_handler
; This is the common *gateway* to save CPU state and restore it while executing
; out ISR
isr_common_stub:
    pusha
    push ds
    push es
    push fs
    push gs
    mov ax, 0x10   ; Load the Kernel Data Segment descriptor!
    mov ds, ax
    mov es, ax
    mov fs, ax
    mov gs, ax
    mov eax, esp   ; Push us the stack
    push eax
    mov eax, _fault_handler
    call eax       ; A special call, preserves the 'eip' register
    pop eax
    pop gs
    pop fs
    pop es
    pop ds
    popa
    add esp, 8     ; Cleans up the pushed error code and pushed ISR number
    iret           ; pops 5 things at once: CS, EIP, EFLAGS, SS, and ESP!

section .bss
resb 8192                        ;8KB for stack
stack_space:
