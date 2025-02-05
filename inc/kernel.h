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

// Structures
/* This defines what the stack looks like after an ISR was running */
struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};

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

// IDT

/* Defines an IDT entry */
struct idt_entry
{
    unsigned short base_lo;
    unsigned short sel;        /* Our kernel segment goes here! */
    unsigned char always0;     /* This will ALWAYS be set to 0! */
    unsigned char flags;       /* Set using the above table! */
    unsigned short base_hi;
} __attribute__((packed));

struct idt_ptr
{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

/* Declare an IDT of 256 entries. Although we will only use the
*  first 32 entries in this tutorial, the rest exists as a bit
*  of a trap. If any undefined IDT entry is hit, it normally
*  will cause an "Unhandled Interrupt" exception. Any descriptor
*  for which the 'presence' bit is cleared (0) will generate an
*  "Unhandled Interrupt" exception */
extern struct idt_entry idt[256];
extern struct idt_ptr _idtp;

/* This exists in 'start.asm', and is used to load our IDT */
extern void _idt_load();
extern void _isr0();

void _fault_handler(struct regs *r);
void idt_install();
void isrs_install();
void idt_set_gate(
    unsigned char num,
    unsigned long base,
    unsigned short sel,
    unsigned char flags
);

#endif
