#include "../inc/kernel.h"

void isrs_install() {
    idt_set_gate(0, (unsigned)_isr0, 0x08, 0x8E);
}

unsigned char *exception_messages[] = {
    "Division By Zero"
};

void _fault_handler(struct regs *r) {
    if (r->int_no < 32) {
        print_nl();
        print_string(exception_messages[r->int_no], WHITE_COLOR);
        print_nl();
        print_string(" Exception. System Halted!", WHITE_COLOR);
        print_nl();
        __asm__ volatile ("cli; hlt"); // TODO: REPLACE WITH PROPER PANIC/HALT
    }
}
