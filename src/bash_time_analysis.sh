#!/bin/bash

tot1=0
tot2=0
tot3=0
tot4=0
declare -a average_array1
declare -a average_array2
declare -a average_array3
declare -a average_array4
echo "Running exe."
for((j = 1 ; j <= 100 ; j++)); do
    echo "Single Threaded Merge Sort : Run number : $j"
    g++ -o mergeSort ./sourcecode/mergeSort.cpp
    time1=$(./mergeSort)
    echo "Time taken for this run is : $time1"
    tot1=$((tot1+time1))

    echo "Single Threaded Quick Sort : Run number : $j"
    g++ -o quickSort ./sourcecode/quickSort.cpp
    time2=$(./quickSort)
    echo "Time taken for this run is : $time2"
    tot2=$((tot2+time2))

    echo "Multi Threaded Merge Sort : Run number : $j"
    g++ -o multimergeSort ./sourcecode/mergeSortMultithreaded.cpp
    time3=$(./multimergeSort)
    echo "Time taken for this run is : $time3"
    tot3=$((tot3+time3))

    echo "Multi Threaded Quick Sort : Run number : $j"
    g++ -o multiquickSort ./sourcecode/quickSortMultithreaded.cpp
    time4=$(./multiquickSort)
    echo "Time taken for this run is : $time4"
    tot4=$((tot4+time4))


done

avg1=$((tot1/100))
echo "Average time taken for Single Threaded Merge Sort is : $avg1"
average_array1=(${avg1})

avg2=$((tot2/100))
echo "Average time taken for Single Threaded Quick Sort is : $avg2"
average_array2=(${avg2})

avg3=$((tot3/100))
echo "Average time taken for Multi Threaded Merge Sort is : $avg3"
average_array3=(${avg3})

avg4=$((tot4/100))
echo "Average time taken for Multi Threaded Merge Sort is : $avg4"
average_array4=(${avg4})

echo "$average_array1" >> mergeresult.txt

echo "$average_array2" >> quickresult.txt

echo "$average_array3" >> multimergeresult.txt

echo "$average_array4" >> multiquickresult.txt
