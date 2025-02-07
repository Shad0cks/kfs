# include "../inc/kernel.h"
# include "../inc/gdt.h"
unsigned short* terminal_buffer;
unsigned int vga_index; 

struct IDTR {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

void printIDTnGDTDebug() {
     struct GDTPtr gdtr;
    // Store IDT register contents into idtr structure
    asm volatile ("sgdt %0" : "=m"(gdtr));
    print_string("gdtr.base: ", WHITE_COLOR);
    print_nl();
    print_hex(&(gdtr.base), sizeof(unsigned int));
    print_nl();
    print_string("gdtr.limit: ", WHITE_COLOR);
    print_nl();
    print_hex(&(gdtr.limit), sizeof(unsigned short));

    print_string("_isr0 address: ", WHITE_COLOR);
    print_nl();
    print_hex(_isr0, 4);
    print_nl();
    print_string("idt: ", WHITE_COLOR);
    print_nl();
    print_hex(idt, sizeof(struct idt_entry));
    print_nl();
    print_string("idtp: ", WHITE_COLOR);
    print_nl();
    print_hex(&_idtp, sizeof(struct idt_ptr));
    print_nl();
    struct IDTR idtr;

    // Store IDT register contents into idtr structure
    asm volatile ("sidt %0" : "=m"(idtr));
    print_string("idtr.base: ", WHITE_COLOR);
    print_nl();
    print_hex(&(idtr.base), sizeof(unsigned int));
    print_nl();
    print_string("idtr.limit: ", WHITE_COLOR);
    print_nl();
    print_hex(&(idtr.limit), sizeof(unsigned short));
}

void main(void)
{
    // SCREEN INIT
    terminal_buffer = (unsigned short *)VGA_ADDRESS;
    vga_index = 0;
    // GOOD PRACTICE TO CLEAR THE SCREEN AT THE VERY BEGINING
    clear_screen();
    // SYSTEM INITIALISATION
    init_gdt();
    idt_install();
    isrs_install();
    irq_install();
    // Enable CPU interruptions reception
    __asm__ __volatile__ ("sti");
    // PRINT WELCOME AND FIRST PROMPT
    print_string("-------WELCOME TO KFS-----", RED);
    print_nl();
    print_nl();
    print_start_cmd();
    move_cursor();
    // PRINT GDT AND IDT DEBUG
    // printIDTnGDTDebug();

    while (1) {
    }
}
