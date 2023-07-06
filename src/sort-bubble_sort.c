
void swap(int* arr, int i) {
    int tmp = arr[i];
    arr[i] = arr[i+1];
    arr[i+1] = tmp;
}

int * bubble_sort(int* arr, int size) {
    for (int i = size; i > 0; i--) {
        for (int j = 0; j < i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr, j);
            }
        }
    }
    return arr;
}

// TEST

#include <stdio.h>
#include "util.h"

#define SIZE 10

int main() {
    int arr[SIZE] = {6,3,5,8,2,7,4,1,9,5};
    printf("1. Initial Array: ");
    print_array(arr, SIZE);
    bubble_sort(arr, SIZE);
    printf("2. Sorted Array: ");
    print_array(arr, SIZE);
}
