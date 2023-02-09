
int
binarySearch(int arr[], int x, int low, int high)
{
    // Repeat until the pointers low and high meet each other
    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (arr[mid] == x)
            return mid;

        if (arr[mid] < x)
            low = mid + 1;

        else
            high = mid - 1;
    }
    return -1;
}

// TEST

#include <stdio.h>
#include "Util.h"

#define SIZE 10

int
main()
{
    int arr[SIZE] = {6,3,5,8,2,7,4,1,9,5};
    
    int value = 7;
    int res = binarySearch(arr, value, 0, SIZE);
    printf("Value at index: %d => %d\n", value, res);
    printArray(arr, SIZE);
}
