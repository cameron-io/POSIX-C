#include "bubble_sort.h"

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
