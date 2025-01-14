#include <stdio.h>
#include "queue.h"

int main() {
    queue_init();
    queue_add("Ford");
    queue_add("Chevrolet");
    queue_add("Dodge");
    queue_add("Ferrari");
    queue_add("Lamborghini");
    printf("Queue 1:\n");
    queue_log();
    printf("\n");
    queue_remove();
    queue_remove();
    printf("Queue 2:\n");
    queue_log();

    return 0;
}
