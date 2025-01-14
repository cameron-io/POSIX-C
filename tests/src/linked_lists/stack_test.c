#include <stdio.h>
#include "stack.h"

int main() {
    stack_init();
    stack_add("Ford");
    stack_add("Chevrolet");
    stack_add("Dodge");
    printf("Stack 1:\n");
    stack_log();
    printf("\n");
    stack_remove();
    printf("Stack 2:\n");
    stack_log();
}