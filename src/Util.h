
#ifndef __UTIL__
#define __UTIL__

#include <stdio.h>

void print_array(int arr[], int size)
{
    printf("[");
    for (int i = 0; i < size-1; i++) {
        printf("%d, ", arr[i]);
    }
    printf("%d]\n", arr[size-1]);
}

#endif
