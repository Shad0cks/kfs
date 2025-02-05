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
    while (index < 80 * 25) {
        terminal_buffer[index] = ' ';
        index += 1;
    }
    vga_index = 0;
}

void print_memory_bytes(void *address) {
    unsigned char *ptr = (unsigned char *)address; // Treat address as a byte pointer

    for (int i = 0; i < sizeof(void *); i++) {  // Print each byte in the pointer size
        char hex[3];  // Store 2 hex digits + null terminator
        unsigned char byte = ptr[i];

        // Convert byte to hexadecimal string
        hex[0] = "0123456789ABCDEF"[byte >> 4];   // Get high nibble
        hex[1] = "0123456789ABCDEF"[byte & 0x0F]; // Get low nibble
        hex[2] = '\0';

        print_char(hex[0], WHITE_COLOR);
        print_char(hex[1], WHITE_COLOR);
        print_char(' ', WHITE_COLOR);  // Space separator
    }
}

void print_char(char str, unsigned char color)
{
    terminal_buffer[vga_index] = str | (unsigned short)color << 8;
    vga_index++;
    if (vga_index > 80 * 25) {
        clear_screen();
    }
}

void print_string(char* str, unsigned char color)
{
    int index = 0;
    while (str[index]) {
        print_char(str[index], color);
        index++;
    }
}

void print_nl()
{
    vga_index += 80 - (vga_index % 80);
    if (vga_index >= 80 * 25) {
        clear_screen();
    }
}

unsigned char return_ascii(unsigned char nbr)
{
	if (nbr < 10)
		return (nbr + '0');
	else
		return (nbr - 10 + 'A');
}



void print_hex(char *addr, int size) {
    for (int i = 0; i < size; i += 16) { // Parcours par blocs de 16 octets
        // Afficher l'adresse mémoire en hexadécimal
        for (int shift = 28; shift >= 0; shift -= 4) {
            print_char(return_ascii(((unsigned int)(addr + i) >> shift) & 0xF), CYAN);
        }
        print_string(":  ", WHITE_COLOR);

        // Afficher l'hex dump
        for (int j = 0; j < 16; j++) {
            if (i + j < size) {
                unsigned char temp = *(addr + i + j);
                print_char(return_ascii(temp / 16), BROWN);
                print_char(return_ascii(temp % 16), BROWN);
            } else {
                // Si hors des limites, alignement avec espaces
                print_string("  ", WHITE_COLOR);
            }
            print_char(' ', WHITE_COLOR); // Espace entre les octets
        }

        // Séparation entre l'hex dump et les caractères ASCII
        print_string("  ", WHITE_COLOR);

        // Afficher les caractères ASCII
        for (int j = 0; j < 16; j++) {
            if (i + j < size) {
                unsigned char temp = *(addr + i + j);
                if (temp >= 32 && temp <= 126) {
                    print_char(temp, GREEN); // Caractère imprimable
                } else {
                    print_char('.', GREEN);  // Caractère non imprimable
                }
            }
        }

        // Fin de ligne
        print_nl();
    }
}

void memset(char *ptr, unsigned int size) {
    for (int i = 0; i < size; i++) {
        *ptr = 0;
        ptr++;
    }
}

int strcmp(char* s1, char* s2) {
    while (*s1 && *s2) {
        if (*s1 != *s2)
            return (0);
        s1++;
        s2++;
    }
    return ((*s1 == '\0') && (*s2 == '\0'));
}
