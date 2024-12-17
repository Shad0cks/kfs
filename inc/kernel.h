#ifndef KERNEL_H
#define KERNEL_H

#define VGA_ADDRESS 0xB8000 

#define BLACK 0
#define GREEN 2
#define CYAN 3
#define RED 4
#define BROWN 6
#define YELLOW 14
#define WHITE_COLOR 15

#define start_term "[terminal] $ "

extern unsigned int vga_index; 
extern unsigned short* terminal_buffer;

#define GET_STACK_POINTER(x)	asm volatile("mov %%esp, %0" : "=r"(x) ::)
#define GET_STACK_FRAME(x)	asm volatile("mov %%ebp, %0" : "=r"(x) ::)

// Ports I/O
unsigned char inb(unsigned short port);
void outb(unsigned short port, unsigned char value);


// Utils
void print_char(char str, unsigned char color);
void print_nl();
void print_string(char* str, unsigned char color);
int strlen(char * string);
void clear_screen(void);
void print_hex(char * addr, int size);
void memset(char *ptr, unsigned int size);
int strcmp(char* s1, char* s2);

// Keyboard
void print_start_cmd();
void keyboard_handler();
void move_cursor();

// Commands
void exec_command(char *command);

#endif
