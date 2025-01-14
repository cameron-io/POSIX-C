#include <stdio.h>
#include "doubly_linked.h"

int main() {
    dll_init();
    dll_push("Ford");
    dll_push("Chevrolet");
    dll_push("Dodge");
    dll_push("Ferrari");
    dll_push("Lamborghini");
    printf("DLL 1:\n");
    dll_log();
    printf("\n");
    dll_pop();
    dll_pop();
    printf("DLL 2:\n");
    dll_log();

    return 0;
}
