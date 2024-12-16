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

void itoa_hex(unsigned int value) {
    char buffer[9];  // Buffer pour stocker la chaîne hexadécimale (8 caractères + '\0')
    char *p = &buffer[8]; // Pointer au bout du buffer
    *p = '\0';  // Null terminate the string

    do {
        p--;
        unsigned char digit = value & 0xF;  // Récupérer le dernier nibble
        *p = (digit < 10) ? ('0' + digit) : ('a' + digit - 10);  // Convertir en ASCII
        value >>= 4;  // Décaler vers la droite pour traiter le nibble suivant
    } while (value != 0);  // Tant que la valeur n'est pas zéro

    print_char(*p++, WHITE_COLOR);  // Afficher le caractère hexadécimal
    while (*p) {
        print_char(*p++, WHITE_COLOR);  // Afficher les autres caractères
    }
}

unsigned char return_ascii(unsigned char nbr)
{
	if (nbr < 10)
		return (nbr + '0');
	else
		return (nbr - 10 + 'A');
}



void print_hex(char * addr, int size){
    // <addd>: d... .. .. .. .. . .
    // for (int i = 0; i < size; i++) {
    //     itoa_hex(addr[i]);
    //     print_nl();
    // }

    int index = -1;

    while(index++ < 0xffff) {
		unsigned char temp = *(addr + index);

		if (temp >= 32 && temp <= 126)
		{
			print_char(temp, WHITE_COLOR);
		}
		else{
            print_char(return_ascii(temp / 16), WHITE_COLOR);
			print_char(return_ascii(temp % 16), WHITE_COLOR);
        }
		print_char(' ', WHITE_COLOR);
    }
}
