//**************************************************************
//          main test routine for test sort algorithms
//**************************************************************

#include <iostream>
#include <vector>
#include <assert.h>
#include <string> // need include this for string op << usage in show.
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
    // there is bug to print string!!
    for (auto i = t.begin(); i != t.end(); i++)
    {
        std::cout << *i << ' ';
    }
    std::cout << "\n";
}

int main()
{
    //int array[] = { 5, 4, 7, 6, 3, 1 };
    //std::vector<int> testData(array, array + 6);

    std::string str[] = { "S", "O", "R", "T", "E", "X", "A", "M", "P", "L", "E" };
    std::vector<std::string> testData(str, str + 11);


    //SelectionSort(testData.begin(), testData.end());

    InsertionSort(testData.begin(), testData.end());

    assert(isSorted(testData));

    show(testData);

}

