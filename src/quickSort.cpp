#include <iostream>
#include <pthread.h>
#include <chrono>
#include <vector>
#include "quickSort.h"
using namespace std;
using namespace std::chrono;

const int LIST_SIZE = 500000;
std::vector<int> globalList(LIST_SIZE, 0);
std::vector<int> finalArr(LIST_SIZE, 0);

void swap(int* a, int* b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

int helperQuickSort(int lo, int hi)
{
    int p = globalList[hi]; 
    int i = lo - 1;  
 
    for (int j = lo; j < hi; j++) {
        if (globalList[j] < p) {
            i++;
            swap(&globalList[i], &globalList[j]);
        }
    }
    swap(&globalList[i + 1], &globalList[hi]);
    return (i + 1);
}
 
void quickSort(int lo, int hi)
{
    if (lo < hi) {
        int p = helperQuickSort(lo, hi);
        quickSort(lo, p - 1);
        quickSort(p + 1, hi);
    }
}

void mergeSublists(void){ 
    
    int arr2[LIST_SIZE/2];
    for(int p =0; p < LIST_SIZE/2; p++)
        arr2[p] = globalList[p+LIST_SIZE/2];

    int len1 = LIST_SIZE/2;
    int len2 = LIST_SIZE / 2;
    int i = 0, j = 0, k = 0;
 
    while (i < len1 && j < len2)
    {
        if (globalList[i] < arr2[j])
            finalArr[k++] = globalList[i++];
        else
            finalArr[k++] = arr2[j++];
    }
 
    while (i < len1)
        finalArr[k++] = globalList[i++];
 
    while (j < len2)
        finalArr[k++] = arr2[j++];

    for(int i=0; i < LIST_SIZE; i++)
        globalList[i] = finalArr[i];
}

void createList(void){
    for(int i=0; i < LIST_SIZE; i++){
        globalList[i]=(rand() % 1000000);
    }
}

int main(){

    createList();
    auto start = high_resolution_clock::now();
    quickSort(0, LIST_SIZE-1);
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    
    cout << "Total execution time: " << duration.count() << "ms" << endl;
    return 0;
}

