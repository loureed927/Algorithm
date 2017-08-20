//**************************************************************
//          main test routine for test sort algorithms
//**************************************************************

#include <iostream>
#include <vector>
#include <assert.h>
#include <string> // need include this for string op << usage in show.
#include "SelectionSort.h"
#include "InsertionSort.h"
#include "ShellSort.h"
#include "MergeSort.h"
#include "QuickSort.h"

// Test array entries are in order.
template<class T>
bool isSorted(T t)
{
    // note iterator should keep valid to t.end()-1 since we are using *(i+1) for comparison.
    for (auto i = t.begin(); i != t.end() -1; i++)
    {
        if (*i > *(i + 1))
            return false;
    }

    return true;
}

// Print the array.
template<class T>
void show(T t)
{
    for (auto i = t.begin(); i != t.end(); i++)
    {
        std::cout << *i << ' ';
    }
    std::cout << "\n";
}

int main()
{
    int array[] = { 5, 4, 7, 6, 3, 1 };
    std::vector<int> testData(array, array + 6);

    //std::string str[] = { "S", "O", "R", "T", "E", "X", "A", "M", "P", "L", "E" };
    //std::vector<std::string> testData(str, str + 11);

    // elementary sorts
    //SelectionSort(testData.begin(), testData.end());
    //InsertionSort(testData.begin(), testData.end());
    //ShellSort(testData.begin(), testData.end());

    // merge sort
    //MergeSortTD(testData, 0, testData.size()-1);
    //MergeSortBU(testData, 0, testData.size() - 1);

    // quick sort
    std::string str[] = { "K", "R", "A", "T", "E", "L", "E", "P", "U", "I", "M", "Q", "C", "X", "O", "S" };
    std::vector<std::string> testDataQ(str, str + 15);
    QuickSort(testDataQ, 0, testDataQ.size() - 1);

    // validate and print result
    assert(isSorted(testData));
    show(testData);
}

