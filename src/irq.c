#include "../inc/kernel.h"

void *irq_routines[17] =
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0, 0
};

// IRQ ROUTINES INTERFACE

void irq_install_handler(int irq, void (*handler)(struct regs *r)) {
    irq_routines[irq] = handler;
}

void irq_uninstall_handler(int irq) {
    irq_routines[irq] = 0;
}

// Program PIC to received IRQ from ISR IDs 32
void irq_remap(void)
{
    outb(0x20, 0x11);
    outb(0xA0, 0x11);
    outb(0x21, 0x20);
    outb(0xA1, 0x28);
    outb(0x21, 0x04);
    outb(0xA1, 0x02);
    outb(0x21, 0x01);
    outb(0xA1, 0x01);
    outb(0x21, 0x0);
    outb(0xA1, 0x0);
}

void whatswrong() {
    print_nl();
    print_string("What's wrong with you ? D_D", RED);
}

void irq_install() {
    // PIC REMAP
    irq_remap();
    // HANDLE EVERY IRQ POSSIBLE
    idt_set_gate(32, (unsigned)_irq0, 0x08, 0x8E);
    idt_set_gate(33, (unsigned)_irq1, 0x08, 0x8E);
    idt_set_gate(34, (unsigned)_irq2, 0x08, 0x8E);
    idt_set_gate(35, (unsigned)_irq3, 0x08, 0x8E);
    idt_set_gate(36, (unsigned)_irq4, 0x08, 0x8E);
    idt_set_gate(37, (unsigned)_irq5, 0x08, 0x8E);
    idt_set_gate(38, (unsigned)_irq6, 0x08, 0x8E);
    idt_set_gate(39, (unsigned)_irq7, 0x08, 0x8E);
    idt_set_gate(40, (unsigned)_irq8, 0x08, 0x8E);
    idt_set_gate(41, (unsigned)_irq9, 0x08, 0x8E);
    idt_set_gate(42, (unsigned)_irq10, 0x08, 0x8E);
    idt_set_gate(43, (unsigned)_irq11, 0x08, 0x8E);
    idt_set_gate(44, (unsigned)_irq12, 0x08, 0x8E);
    idt_set_gate(45, (unsigned)_irq13, 0x08, 0x8E);
    idt_set_gate(46, (unsigned)_irq14, 0x08, 0x8E);
    idt_set_gate(47, (unsigned)_irq15, 0x08, 0x8E);
    idt_set_gate(48, (unsigned)_irsw0, 0x08, 0x8E);
    // ASSIGN CUSTOM FUNCTIONS LINKED WITH RECEIVED IRQ IDs
    irq_install_handler(1, keyboard_handler);
    irq_install_handler(16, whatswrong);
}

// IRQ ENTRYPOINT
void _irq_handler(struct regs *r)
{
    // Handler selected from IRQ number
    void (*handler)(struct regs *r);

    handler = irq_routines[r->int_no - 32];
    if (handler) {
        handler(r);
    }
    // SEND EOI
    if (r->int_no >= 40) { // IF SLAVE PIC INVOLVED, SEND ALSO EIO
        outb(0xA0, 0x20);
    }
    // Master EOI
    outb(0x20, 0x20);
}
