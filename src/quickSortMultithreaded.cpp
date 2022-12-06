#include <iostream>
#include <pthread.h>
#include <algorithm>
#include <chrono>
#include <vector>
#include <fstream>
#include <unistd.h>

using namespace std;
using namespace std::chrono;


int LIST_SIZE = 1000000;
const int NUM_THREADS = 3;

vector<int> globalList(LIST_SIZE, 0);
vector<int> finalArr(LIST_SIZE, 0); 

std::chrono::time_point<std::chrono::system_clock> startThread1, stopThread1;
std::chrono::time_point<std::chrono::system_clock> startThread2, stopThread2;
std::chrono::time_point<std::chrono::system_clock> startThread3, stopThread3;

pthread_mutex_t myMutex0 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t myMutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t myMutex2 = PTHREAD_MUTEX_INITIALIZER;

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
        int pi = helperQuickSort(lo, hi);
        quickSort(lo, pi - 1);
        quickSort(pi + 1, hi);
    }
}


void *quickSort0(void* arg){ //first half
    startThread1 = high_resolution_clock::now();
    pthread_mutex_lock(&myMutex0);
    quickSort(0, LIST_SIZE/2 -1);
    pthread_mutex_unlock(&myMutex0);
    stopThread1 = high_resolution_clock::now();
}

void *quickSort1(void* arg){ //second half
    startThread2 = high_resolution_clock::now();
    pthread_mutex_lock(&myMutex1);
    quickSort(LIST_SIZE/2 , LIST_SIZE-1);
    pthread_mutex_unlock(&myMutex1);
    stopThread2 = high_resolution_clock::now();
}


void* mergeSublists(void* arg){ //merge both halves
    startThread3 = high_resolution_clock::now();
    pthread_mutex_lock(&myMutex2);
   
    int arr2[LIST_SIZE/2];
    for(int p =0; p < LIST_SIZE/2; p++)
        arr2[p] = globalList[p+ LIST_SIZE/2];

    int n1 = LIST_SIZE/2;
    int n2 = LIST_SIZE / 2;
    int i = 0, j = 0, k = 0;
 
    while (i<n1 && j <n2)
    {
        if (globalList[i] < arr2[j])
            finalArr[k++] = globalList[i++];
        else
            finalArr[k++] = arr2[j++];
    }
 
    while (i < n1)
        finalArr[k++] = globalList[i++];
 
    while (j < n2)
        finalArr[k++] = arr2[j++];

    for(int i=0; i < LIST_SIZE; i++)
        globalList[i] = finalArr[i];

    pthread_mutex_unlock(&myMutex2);
    stopThread3 = high_resolution_clock::now();
}

void createList(void){
    for(int i=0; i<LIST_SIZE; i++){
        globalList[i]=(rand() % 1000000);
    }
}

void selectionSort(void){
    
    for(int i=0;i< LIST_SIZE;i++){
        int min_idx = i;
        for(int j= i+1; j < LIST_SIZE;j++){
            if(globalList[min_idx] > globalList[j]){
                min_idx = j;
            }
        }
        
        if(min_idx != i){
            int temp = globalList[i];
            globalList[i] = globalList[min_idx];
            globalList[min_idx] = temp;
        }
    }
}


void invokeQuickSortMultiThreaded(void){
    if(LIST_SIZE < 100){
        selectionSort();
    }
    else{
        pthread_t tid[NUM_THREADS];

        pthread_create(&tid[0], NULL, quickSort0, (void*)NULL);
        pthread_create(&tid[1], NULL, quickSort1, (void*)NULL);
        pthread_join(tid[0], NULL);
        pthread_join(tid[1], NULL);
        
        pthread_create(&tid[2], NULL, mergeSublists, (void*)NULL);
        pthread_join(tid[2], NULL);
    }
}

int main(){

    createList();
   
    auto start = high_resolution_clock::now();
    invokeQuickSortMultiThreaded();
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    auto durationThread1 = duration_cast<milliseconds>(stopThread1 - startThread1);
    auto durationThread2 = duration_cast<milliseconds>(stopThread2 - startThread2);
    auto durationThread3 = duration_cast<milliseconds>(stopThread3 - startThread3);
    
    cout << "Total execution time: " << duration.count() << "ms" << endl;
    cout << "Thread1 time: " << durationThread1.count() << "ms "<< endl;
    cout << "Thread2 time: " << durationThread2.count() << "ms "<< endl;
    cout << "Thread3 time: " << durationThread3.count() << "ms " << endl;
    
    pthread_exit(0);
    return 0;
}