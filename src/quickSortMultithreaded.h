#ifndef __QUICKSORT_MULTITHREADED_H__
#define __QUICKSORT_MULTITHREADED_H__


void swap(int* a, int* b);
int helperQuickSort(int lo, int hi);
void quickSort(int lo, int hi);
void createList(void);
void selectionSort(void);
void *quickSort0(void* arg);
void *quickSort1(void* arg);
void* mergeSublists(void* arg);
void invokeQuickSortMultiThreaded(void);

#endif