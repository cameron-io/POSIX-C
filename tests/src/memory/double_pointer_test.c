#include <stdlib.h>

void allocateMemory(int **ptr) {
    *ptr = (int*)malloc(sizeof(int)); // Modify the pointer itself
    if (*ptr == NULL) {
        // Handle memory allocation failure
    }
    **ptr = 5; // Dereference twice to access the value
}

int main() {
    int *p = NULL; 
    allocateMemory(&p); 
    // Now 'p' points to the dynamically allocated memory
    *p = 5;

    return 0;
}
