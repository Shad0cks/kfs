# include "../inc/kernel.h"
# include "../inc/gdt.h"

unsigned short* terminal_buffer;
unsigned int vga_index; 

void main(void)
{
    terminal_buffer = (unsigned short *)VGA_ADDRESS;
    vga_index = 0;

    init_gdt();

    clear_screen();
    print_string("-------WELCOME TO KFS-----", RED);
    print_nl();
    print_nl();
    print_start_cmd();
    move_cursor();

    // print_hex((char *)(GDT_ADDRESS), 70);

    while (1) {
        keyboard_handler();
    }
}
