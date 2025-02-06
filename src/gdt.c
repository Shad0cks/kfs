#include "../inc/gdt.h"
#include "../inc/kernel.h"

struct GDTEntry gdt[7];
struct GDTPtr *gdtp = GDT_ADDRESS;

void create_descriptor(
    struct GDTEntry* entry,
    unsigned int base,
    unsigned int limit,
    unsigned char access,
    unsigned char gran
) {
    entry->base_low = (unsigned short)(base & 0xFFFF);        // Partie basse de la base
    entry->base_middle = (signed char)((base >> 16) & 0xFF);  // Partie intermédiaire de la base
    entry->base_high = (signed char)((base >> 24) & 0xFF);    // Partie haute de la base
    entry->limit_low = (unsigned short)(limit & 0xFFFF);      // Partie basse de la limite
    entry->granularity = (signed char)((limit >> 16) & 0x0F); // Bits de limite haute
    entry->granularity |= (gran) & 0xF0;                // Granularité et autres flags
    entry->access = access;              // Bits d'accès
}

void debug_gdt() {
    print_string("gdt: ", WHITE_COLOR);
    print_nl();
    print_hex(gdt, sizeof(struct GDTEntry) * 7);
    print_nl();
    print_string("gdtp: ", WHITE_COLOR);
    print_nl();
    print_hex(&gdtp, sizeof(struct GDTPtr));
    print_nl();
}

void init_gdt(){
    gdtp->limit = (sizeof(struct GDTEntry) * 7) - 1;
    gdtp->base = &gdt;

    create_descriptor(&gdt[0], 0, 0, 0, 0);
    create_descriptor(&gdt[1], 0, 0xFFFFF, (unsigned char)GDT_CODE_PL0, 0xCF);
    create_descriptor(&gdt[2], 0, 0xFFFFF, (unsigned char)GDT_DATA_PL0, 0xCF);
    create_descriptor(&gdt[3], 0, 0xFFFFF, (unsigned char)GDT_STACK_PL0, 0xCF);
    create_descriptor(&gdt[4], 0, 0xFFFFF, (unsigned char)GDT_CODE_PL3, 0xCF);
    create_descriptor(&gdt[5], 0, 0xFFFFF, (unsigned char)GDT_DATA_PL3, 0xCF);
    create_descriptor(&gdt[6], 0, 0xFFFFF, (unsigned char)GDT_STACK_PL3, 0xCF);

    // debug_gdt();

    setGdt(GDT_ADDRESS);
}
