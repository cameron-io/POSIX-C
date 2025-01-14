#include <stdio.h>
#include "lib/sorting/quick_sort.h"
#include "../include/util.h"

#define SIZE 10

int main() {
    int arr[SIZE] = {6,3,5,8,2,7,4,1,9,5};
    printf("1. Initial Array: ");
    print_array(arr, SIZE);
    quick_sort(arr, 0, SIZE);
    printf("2. Sorted Array: ");
    print_array(arr, SIZE);
}
