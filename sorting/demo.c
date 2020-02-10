
#include <stdio.h>
#include "sort.h"

/*
 * Demo code to test different sorting algo
 */

int main()
{
    /* Selection sort */
    {
        int arr[] = {8, 7, 6, 5, 4, 3, 2, 1};
        unsigned int arrLen = sizeof(arr) / sizeof(int);

        selectionSort(arr, arrLen);
        printf("Section Sorted arr:\n");
        for(unsigned int i = 0; i < arrLen; i++)
        {
            printf("%d ", arr[i]);
        }
        putchar('\n');
    }

    /* Insertion sort */
    {
        int arr[] = {8, 7, 6, 5, 4, 3, 2, 1};
        unsigned int arrLen = sizeof(arr) / sizeof(int);

        insertionSort(arr, arrLen);
        printf("Insertion Sorted arr:\n");
        for(unsigned int i = 0; i < arrLen; i++)
        {
            printf("%d ", arr[i]);
        }
        putchar('\n');
    }

    /* Bubble sort */
    {
        int arr[] = {8, 7, 6, 5, 4, 3, 2, 1};
        unsigned int arrLen = sizeof(arr) / sizeof(int);

        bubbleSort(arr, arrLen);
        printf("Bubble Sorted arr:\n");
        for(unsigned int i = 0; i < arrLen; i++)
        {
            printf("%d ", arr[i]);
        }
        putchar('\n');
    }

    /* Quick sort */
    {
        int arr[] = {8, 7, 6, 5, 4, 3, 2, 1};
        unsigned int arrLen = sizeof(arr) / sizeof(int);

        quickSort(arr, 0, arrLen - 1);
        printf("Quick Sorted arr:\n");
        for(unsigned int i = 0; i < arrLen; i++)
        {
            printf("%d ", arr[i]);
        }
        putchar('\n');
    }
    return 0;
}
