
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

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
    
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// TEST

#include <stdio.h>
#include "Util.h"

#define SIZE 10

int main() {
    int arr[SIZE] = {6,3,5,8,2,7,4,1,9,5};
    
    printArray(arr, SIZE);
    printf("* Performing QuickSort...\n");
    quickSort(arr, 0, SIZE);
    printArray(arr, SIZE);
}
