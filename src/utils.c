# include "../inc/kernel.h"

int strlen(char * string){
    int i = 0;

    while (string[i]){
        i++;
    }
    return i;
}

void clear_screen(void)
{
    int index = 0;
    /* there are 25 lines each of 80 columns;
       each element takes 2 bytes */
    while (index < 80 * 25 * 2) {
        terminal_buffer[index] = ' ';
        index += 2;
    }
}

void print_char(char str, unsigned char color)
{    
    terminal_buffer[vga_index] = str | (unsigned short)color << 8;
    vga_index++;
}


void print_string(char* str, unsigned char color)
{
    int index = 0;
    while (str[index]) {
        print_char(str[index], color);
        index++;
    }
}

void print_nl(){
    vga_index += 80 - (vga_index % 80);
}
