#include <stdio.h>
#include <assert.h>
#include "binary_search.h"
#include "../include/util.h"

#define SIZE 10

int main() {
    int arr[SIZE] = {6,3,5,8,2,7,4,1,9,5};
    
    int value = 7;
    int result = binary_search(arr, value, 0, SIZE);

    assert(value == 7 && result == 5);
    printf("Value at index: %d => %d\n", value, result);

    print_array(arr, SIZE);
}
