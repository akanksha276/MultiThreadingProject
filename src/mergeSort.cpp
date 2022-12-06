#include <iostream>
#include <pthread.h>
#include <vector>
#include <chrono>
#include <algorithm>


using namespace std;
using namespace std::chrono;

const int LIST_SIZE = 1000000;

std::vector<int> globalList(LIST_SIZE);
std::vector<int> finalArr(LIST_SIZE, 0);

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


void createList(void){
    for(int i=0; i<LIST_SIZE; i++){
        globalList[i]=(rand() % 1000000);
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

int main(){
    
    createList();
    
    auto start = high_resolution_clock::now();
    mergesortVector(0, LIST_SIZE-1);
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    
    cout << "Total execution time: " << duration.count() << "ms" << endl;

    return 0;
}

