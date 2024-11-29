# include "../inc/kernel.h"

#define MAX_SCANCODE 0x58 // Le scan code maximum pour les caractères imprimables
#define VGA_PORT_COMMAND  0x3D4
#define VGA_PORT_DATA     0x3D5

typedef struct {
    unsigned char scancode;
    char character;
} ScancodeMapping;

ScancodeMapping scancode_map[] = {
    {0x1E, 'a'}, {0x30, 'b'}, {0x2E, 'c'}, {0x20, 'd'}, {0x12, 'e'},
    {0x21, 'f'}, {0x22, 'g'}, {0x23, 'h'}, {0x17, 'i'}, {0x24, 'j'},
    {0x25, 'k'}, {0x26, 'l'}, {0x32, 'm'}, {0x31, 'n'}, {0x18, 'o'},
    {0x19, 'p'}, {0x10, 'q'}, {0x13, 'r'}, {0x1F, 's'}, {0x14, 't'},
    {0x16, 'u'}, {0x2F, 'v'}, {0x11, 'w'}, {0x2D, 'x'}, {0x15, 'y'},
    {0x2C, 'z'}, {0x39, ' '}, {0x0B, '0'}, {0x02, '1'}, {0x03, '2'},
    {0x04, '3'}, {0x05, '4'}, {0x06, '5'}, {0x07, '6'}, {0x08, '7'},
    {0x09, '8'}, {0x0A, '9'}
};


void move_cursor() {

    // Envoi de la position basse du curseur
    outb(VGA_PORT_COMMAND, 0x0F);         // Sélectionner le registre de position basse
    outb(VGA_PORT_DATA, (unsigned char)(vga_index & 0xFF));

    // Envoi de la position haute du curseur
    outb(VGA_PORT_COMMAND, 0x0E);         // Sélectionner le registre de position haute
    outb(VGA_PORT_DATA, (unsigned char)((vga_index >> 8) & 0xFF));
    print_char(' ', GREEN);
    vga_index -= 1;
}

void print_start_cmd(){
    print_string(start_term, WHITE_COLOR);
}



unsigned char get_scancode()
{
    unsigned char inputdata;
    inputdata = inb(0x60);
    return inputdata;
}

#define SCANCODE_MAP_SIZE (sizeof(scancode_map) / sizeof(ScancodeMapping))

int canSend = 0;
int clicked = 0;
int shift_key = 0;

void code_selector(unsigned char scancode){
    switch (scancode)
    {
        case 0x0E: // del
            if (vga_index % 80 != strlen(start_term)){
                vga_index -= 1;
                print_char(' ', WHITE_COLOR);
                vga_index -= 1;
            }
            clicked = 1;
            canSend = 0;
            break;
        case 0x1C: // enter
            print_nl();
            print_start_cmd();
            clicked = 1;
            canSend = 0;
            break;
        default:
            for (int i = 0; i < SCANCODE_MAP_SIZE; i++) {
                if (scancode_map[i].scancode == scancode) {
                    if (scancode_map[i].character >= 'a' && scancode_map[i].character <= 'z' && shift_key){
                        print_char(scancode_map[i].character - 32, WHITE_COLOR);  
                    }else{
                        print_char(scancode_map[i].character, WHITE_COLOR);  
                    }
                    clicked = 1;  
                    canSend = 0;
                    break;
                }
            }
            break;
    }
}

void keyboard_handler() {
    unsigned char scancode;
    
    scancode = get_scancode();


    if (scancode == 0x2A || scancode == 0x36) {
        shift_key = 1;  // Shift enfoncé
    } else if (scancode == 0xAA || scancode == 0xB6) {
        shift_key = 0;  // Shift relâché
    }

    if (scancode & 0x80) { // Touche relâchée
        clicked = 0;
        canSend = 1;
    } else {

        if (canSend && clicked == 0) {
            code_selector(scancode);
            move_cursor(vga_index);
        }
    }
}

