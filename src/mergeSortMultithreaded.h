#ifndef __MERGESORT_MULTITHREADED_H__
#define __MERGESORT_MULTITHREADED_H__

void mergeVector(int start, int end);
void mergesortVector(int start, int end);
void* mergeSort0(void* arg);
void* mergeSort1(void* arg);
void* mergeMergeSort(void* arg);
void createList(void);
void invokeMergeSortMultiThreaded(void);
void selectionSort(void);


#endif