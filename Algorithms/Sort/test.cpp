#include <iostream>
#include <vector>
#include "SelectionSort.h"


int main()
{
    std::vector<int> testData;
    testData.push_back(5);
    testData.push_back(4);
	testData.push_back(3);
    testData.push_back(2);
    testData.push_back(1);

    SelectionSort(testData.begin(), testData.end());

}

