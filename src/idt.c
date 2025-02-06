#include "../inc/kernel.h"

struct idt_entry idt[256]; // Where the IDT is actually stored
struct idt_ptr _idtp;      // IDT ptr that will be send to the CPU

void idt_set_gate(
    unsigned char num,
    unsigned long base,
    unsigned short sel,
    unsigned char flags
) {
    // Assign the address of the subroutine
    idt[num].base_lo = base & 0xFFFF;
    idt[num].base_hi = (base >> 16) & 0xFFFF;
    // Set flags and additionnal data to the IDT entry
    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void idt_install() {
    // Set the pointer to the IDT to idtp
    _idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    _idtp.base = &idt;
    // Clear the current IDT
    memset(idt, sizeof(struct idt_entry) * 256);
    _idt_load();
}
