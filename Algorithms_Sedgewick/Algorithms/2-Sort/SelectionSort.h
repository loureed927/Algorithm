//**************************************************************
//          selection sort
//**************************************************************

template<class RandomAccessIterator>
void SelectionSort(RandomAccessIterator first, RandomAccessIterator last)
{
    // my first version forgets to find min element of inner loop, which leads to massive extra swap
    //for (RandomAccessIterator i = first; i != last; ++i)
    //{
    //    for (RandomAccessIterator j = i + 1; j != last; ++j)
    //    {
    //        if (*i > *j)
    //            std::swap(*i, *j)
    //    }
    //}

    for (RandomAccessIterator i = first; i != last; ++i)
    {
        // find min index
        RandomAccessIterator min = i;
        for (RandomAccessIterator j = i + 1; j != last; ++j)
        {
            if (*min > *j)
                min = j;
        }

        std::swap(*i, *min);
    }
}
