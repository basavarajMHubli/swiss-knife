
#ifndef __SORT_H__
#define __SORT_H__
/**
 * @file sort.h
 * @brief Sorting algorithms
 * @author Basavaraj M. H.
 * @version 0.1
 * @date 2020-02-10
 */

/**
* @brief
*
* @param a
* @param b
*/
static void _swap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

/**
* @brief
*
* @param arr
* @param arrLen
*/
static void selectionSort(int *arr, unsigned int arrLen)
{
    int minIdx;

    for (unsigned int i = 0; i < arrLen - 1; i++)
    {
        minIdx = i;
        for (unsigned int j = i + 1; j < arrLen; j++)
        {
            if (arr[j] < arr[minIdx])
            {
                minIdx = j;
            }
        }
		_swap(&arr[minIdx], &arr[i]);
    }
}

/**
* @brief
*
* @param arr
* @param arrLen
*/
static void insertionSort(int *arr, unsigned int arrLen)
{
    int key;
    int j;

    for (unsigned int i = 1; i < arrLen; i++)
    {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

/**
* @brief
*
* @param arr
* @param arrLen
*/
static void bubbleSort(int *arr, unsigned int arrLen)
{
    for (unsigned int i = 0; i < arrLen - 1; i++)
    {
        for (unsigned int j = 0; j < arrLen - i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
				_swap(&arr[j], &arr[j + 1]);
            }
        }
    }
}

/**
* @brief
*
* @param arr
* @param low
* @param high
*
* @return
*/
static int _partition(int *arr, int low, int high)
{
    int pivot = arr[high];
    int pIdx = low;

    for (int j = low; j < high; j++)
    {
        if (arr[j] < pivot)
        {
            _swap(&arr[pIdx], &arr[j]);
            pIdx++;
        }
    }
    _swap(&arr[pIdx], &arr[high]);
    return pIdx;
}

/**
 * @brief
 *
 * @param arr
 * @param low
 * @param high
 */
static void quickSort(int *arr, int low, int high)
{
    int pIdx;

    if (low < high)
    {
        pIdx = _partition(arr, low, high);

        quickSort(arr, low, pIdx - 1);
        quickSort(arr, pIdx + 1, high);
    }
}
#endif /* __SORT_H__ */
