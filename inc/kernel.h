#ifndef KERNEL_H
#define KERNEL_H

#define VGA_ADDRESS 0xB8000 

#define BLACK 0
#define GREEN 2
#define RED 4
#define YELLOW 14
#define WHITE_COLOR 15

#define start_term "[terminal] $ "

extern unsigned int vga_index; 
extern unsigned short* terminal_buffer; 


// Ports I/O
unsigned char inb(unsigned short port);
void outb(unsigned short port, unsigned char value);


// Utils
void print_char(char str, unsigned char color);
void print_nl();
void print_string(char* str, unsigned char color);
int strlen(char * string);
void clear_screen(void);

// Keyboard
void print_start_cmd();
void keyboard_handler();
void move_cursor();


#endif