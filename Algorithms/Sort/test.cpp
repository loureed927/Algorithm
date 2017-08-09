#include <iostream>
#include <vector>
#include <assert.h>
#include "SelectionSort.h"
#include "InsertionSort.h"

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
    std::vector<int> testData;
    testData.push_back(5);
    testData.push_back(4);
    testData.push_back(7);
    testData.push_back(6);
    testData.push_back(3);
    testData.push_back(1);

    //SelectionSort(testData.begin(), testData.end());

    InsertionSort(testData.begin(), testData.end());

    assert(isSorted(testData));

    show(testData);

}

