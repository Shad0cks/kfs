#include "../inc/kernel.h"

static void coucou() {
    int a = 42;
    char b[6] = "COUCOU";
    char c = 'Z';
    int sp;
    int bp;

    GET_STACK_POINTER(sp);
    GET_STACK_FRAME(bp);
    print_nl();
    print_hex(sp, bp - sp);
}

static void divByZero() {
    const char impossible = 56 / 0;
    print_hex(&impossible, sizeof(impossible));
}

static void invalidOpCode() {
    // Instruction that trigger an op code invalid interruption
    __asm__ volatile ("ud2");
}

static void triggerReservedInt() {
    // Instruction that interrupt an arbitrary interruption number
    //   -> Here corresponding to a reserved interruption
    __asm__ volatile ("int $0x1E");
}

static void halt() {
    clear_screen();
    print_string("Salut mon pote :'(", WHITE_COLOR);
    print_nl();
    panic();
}

static void hello() {
    // Instruction that interrupt an arbitrary interruption number
    //   -> Here corresponding to a reserved interruption
    __asm__ volatile ("int $0x30");
}

void exec_command(char *command) {
    if (strcmp(command, "coucou") == 1) {
        coucou();
    } else if (strcmp(command, "0")) {
        divByZero();
    } else if (strcmp(command, "badop")) {
        invalidOpCode();
    } else if (strcmp(command, "reservedInt")) {
        triggerReservedInt();
    } else if (strcmp(command, "halt")) {
        halt();
    } else if (strcmp(command, "hello")) {
        hello();
    }
}
