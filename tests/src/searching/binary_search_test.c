#include <stdio.h>
#include "lib/searching/binary_search.h"
#include "../include/util.h"

#define SIZE 10

int main() {
    int arr[SIZE] = {6,3,5,8,2,7,4,1,9,5};
    
    int value = 7;
    int res = binary_search(arr, value, 0, SIZE);
    printf("Value at index: %d => %d\n", value, res);
    print_array(arr, SIZE);
}
