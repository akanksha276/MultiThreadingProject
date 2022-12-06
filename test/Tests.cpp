#include <algorithm>
#include <limits.h>
#include <iostream>
#include <exception>
#include "quickSort.h"
#include "quickSortMultithreaded.h"
#include "mergeSort.h"
#include "mergeSortMultithreaded.h"
#include <vector>

using namespace std;
int SIZE = 100000;

/* QuickSort unit test */
void TEST1(void) {
    vector<int> checkList(SIZE);
    for(int i=0; i< SIZE; i++){
        globalList[i]=(rand() % 1000000);
        checkList[i] = globalList[i];
    }
    sort(checkList.begin(), checkList.end()); //EXPECTED
    quickSort(0, SIZE-1); //ACTUAL

    try{
        for(int i=0; i < SIZE; i++)
        {
            if(globalList[i] != checkList[i])
                throw(1); //Errorno 1 
        }
        std::cout << "TEST1 passed!" << std::endl;
    }
    catch(std::exception& e){
        std::cout << "TEST1 failed. " << std::endl;
    }
  
}

/* MergeSort unit test */
void TEST2(void) {
    vector<int> testList(SIZE);
    vector<int> checkList(SIZE);
    for(int i=0; i< SIZE; i++){
        globalList[i]=(rand() % 1000000);
        checkList[i] = globalList[i];
    }
    sort(checkList.begin(), checkList.end()); //EXPECTED
    mergeVector(0, SIZE-1); //ACTUAL

    try{
        for(int i=0; i < SIZE; i++)
        {
            if(globalList[i] != checkList[i])
                throw(2); //Errorno 2
        }
        std::cout << "TEST2 passed!" << std::endl;
    }
    catch(std::exception& e){
        std::cout << "TEST2 failed. " << std::endl;
    }
}

/* Quick Sort Multithreaded Integration Test */ 
void TEST3(void) {
    vector<int> testList(SIZE);
    vector<int> checkList(SIZE);
    for(int i=0; i< SIZE; i++){
        globalList[i]=(rand() % 1000000);
        checkList[i] = globalList[i];
    }
    sort(checkList.begin(), checkList.end()); //EXPECTED
    invokequickSortMultithreaded(); //ACTUAL

    try{
        if(SIZE < 100){
            throw(3);
        }
        for(int i=0; i < SIZE; i++)
        {
            if(globalList[i] != checkList[i])
                throw(3); //Errorno 3
        }
        std::cout << "TEST3 passed!" << std::endl;
    }
    catch(std::exception& e){
        std::cout << "TEST3 failed. " << std::endl;
    }
}


/* Merge Sort Multithreaded Integration Test */ 
void TEST4(void) {
    vector<int> testList(SIZE);
    vector<int> checkList(SIZE);
    for(int i=0; i< SIZE; i++){
        globalList[i]=(rand() % 1000000);
        checkList[i] = globalList[i];
    }
    sort(checkList.begin(), checkList.end()); //EXPECTED
    invokeMergeSortMultithreaded(); //ACTUAL

    try{
        if(SIZE < 100){
            throw(4);
        }
        for(int i=0; i < SIZE; i++)
        {
            if(globalList[i] != checkList[i])
                throw(4); //Errorno 4
        }
        std::cout << "TEST4 passed!" << std::endl;
    }
    catch(std::exception& e){
        std::cout << "TEST4 failed. " << std::endl;
    }
}
int main(void)
{
    TEST1();
    TEST2();
    TEST3();
    TEST4();

    return 0;
}