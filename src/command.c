#include "../inc/kernel.h"

void coucou() {
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

void exec_command(char *command) {
    if (strcmp(command, "coucou") == 1) {
        coucou();
    }
}
