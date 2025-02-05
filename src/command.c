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

void exec_command(char *command) {
    if (strcmp(command, "coucou") == 1) {
        coucou();
    } else if (strcmp(command, "0")) {
        divByZero();
    }
}
