#include <iostream>
#include <pthread.h>
#include <vector>
#include <chrono>
#include <algorithm>
using namespace std;
using namespace std::chrono;

const int LIST_SIZE = 100000;
const int NUM_THREADS = 3;

vector<int> globalList(LIST_SIZE);
vector<int> finalArr(LIST_SIZE, 0);

pthread_mutex_t myMutex0 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t myMutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t myMutex2 = PTHREAD_MUTEX_INITIALIZER;

std::chrono::time_point<std::chrono::system_clock> startThread1, stopThread1;
std::chrono::time_point<std::chrono::system_clock> startThread2, stopThread2;
std::chrono::time_point<std::chrono::system_clock> startThread3, stopThread3;

void mergeVector(int start, int end){
   
    vector<int> temp;
    int m = (start+end)/2;
    int i = start;
    int j = m + 1;
   
    while (i <= m && j <= end){
        if (globalList[i] <= globalList[j]){
            temp.push_back(globalList[i]);
            ++i;
        }
        else{
            temp.push_back(globalList[j]);
            ++j;
        }
    }
   
    while (i <= m){
        temp.push_back(globalList[i]);
        ++i;
    }
    while (j <= end){
        temp.push_back(globalList[j]);
        ++j;
    }
   
    for (int i = start; i <= end; ++i){
        globalList[i] = temp[i - start];
    }
}

void mergesortVector(int start, int end){
    if (start < end)
    {
        int m = (start + end) / 2;
        mergesortVector(start, m);
        mergesortVector(m + 1, end);
        mergeVector(start, end);
    }
}


void* mergeSort0(void* arg){
    startThread1 = high_resolution_clock::now();
    pthread_mutex_lock(&myMutex0);
    mergesortVector(0, LIST_SIZE/2 -1);
    pthread_mutex_unlock(&myMutex0);
    stopThread1 = high_resolution_clock::now();
}

void* mergeSort1(void* arg){
    startThread2 = high_resolution_clock::now();
    pthread_mutex_lock(&myMutex1);
    mergesortVector(LIST_SIZE/2 , LIST_SIZE-1);
    pthread_mutex_unlock(&myMutex1);
    stopThread2 = high_resolution_clock::now();
}

void* mergeMergeSort(void* arg){ //merge
    startThread3 = high_resolution_clock::now();
    pthread_mutex_lock(&myMutex2);
    mergeVector(0, LIST_SIZE-1);
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

void invokeMergeSortMultiThreaded(void){
    if(LIST_SIZE < 100){
        selectionSort();
    }
    else{
        pthread_t tid[NUM_THREADS];
        pthread_create(&tid[0], NULL, mergeSort0, (void*)NULL);
        pthread_create(&tid[1], NULL, mergeSort1, (void*)NULL);
        
        pthread_join(tid[0], NULL);
        pthread_join(tid[1], NULL);
        pthread_create(&tid[2], NULL, mergeMergeSort, (void*)NULL);
        pthread_join(tid[2], NULL);
    }
}


int main(){
    
    createList();
    auto start = high_resolution_clock::now();
    
    invokeMergeSortMultiThreaded();
    
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

