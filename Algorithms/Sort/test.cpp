#include <iostream>
#include <vector>
#include "SelectionSort.h"
#include "InsertionSort.h"

int main()
{
    std::vector<int> testData;
    testData.push_back(5);
    testData.push_back(4);
    testData.push_back(7);
    testData.push_back(6);
    testData.push_back(3);
    testData.push_back(1);

    //SelectionSort(testData.begin(), testData.end());

    InsertionSort(testData.begin(), testData.end());

}

