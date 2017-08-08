//**************************************************************
//          insertion sort
//**************************************************************

template<class RandomAccessIterator>
void InsertionSort(RandomAccessIterator first, RandomAccessIterator last)
{
    // assume we have a sorted cards
    // how to build container of data type from input interator
    std::vector<int> sorted;
    //need reserve capacity for sorted in case of sorted become invalid when insert element
    sorted.reserve(std::distance(first, last));
    sorted.push_back(*first);

    for (auto next = ++first; next != last; next++)
    {
        bool find = false;
        // find appropriate place for next to fit in sorted.
        for (auto i = sorted.begin(); i != sorted.end(); i++)
        {
            if (*next < *i)
            {
                sorted.insert(i, *next);
                find = true;
                break;
            }
        }

        // if not find element larger than next, push next at the back of sorted.
        if (!find)
            sorted.push_back(*next);
    }

    // assign value to original iterator from sorted
    // this is incorrect.
    for (auto j = sorted.begin(); j != sorted.end(); j++)
    {
        *(first++) = *j;
    }
}

