#include <iostream>

template<class RandomAccessIterator>
void SelectionSort(RandomAccessIterator first, RandomAccessIterator last)
{
    for (RandomAccessIterator i = first; i < last; ++i)
    {
        for (RandomAccessIterator j = i + 1; j < last; ++j)
        {
            if (i > j)
                std::swap(i, j);
        }
    }

}

