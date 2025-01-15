#include "quick_sort.h"

void quick_swap(int arr[], int a, int b) {
    int t = arr[a];
    arr[a] = arr[b];
    arr[b] = t;
}

int quick_partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            quick_swap(arr, i, j);
        }
    }
    quick_swap(arr, i + 1, high);

    return (i + 1);
}

void quick_sort(int arr[], int low, int high) {
    if (low < high) {
        int pi = quick_partition(arr, low, high);
    
        quick_sort(arr, low, pi - 1);
        quick_sort(arr, pi + 1, high);
    }
}
