
void swap(int arr[], int a, int b) {
    int t = arr[a];
    arr[a] = arr[b];
    arr[b] = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr, i, j);
        }
    }
    swap(arr, i + 1, high);

    return (i + 1);
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
    
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}

// TEST

#include <stdio.h>
#include "util.h"

#define SIZE 10

int main() {
    int arr[SIZE] = {6,3,5,8,2,7,4,1,9,5};
    printf("1. Initial Array: ");
    print_array(arr, SIZE);
    quick_sort(arr, 0, SIZE);
    printf("2. Sorted Array: ");
    print_array(arr, SIZE);
}
