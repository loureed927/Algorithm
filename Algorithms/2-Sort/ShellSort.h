//**************************************************************
//          shell sort
//**************************************************************

template<class RandomAccessIterator>
void ShellSort(RandomAccessIterator first, RandomAccessIterator last)
{
    int h = 1;
    int num = std::distance(first, last);

    // find largest increment of h.
    // why use increment sequence like this?
    while (h < num / 3)
        h = 3 * h + 1; // 1, 4, 13,...
    /*
    // version 1
    while (h >= 1)
    {
        for (auto i = first; i + h != last; i++)
        {
            if (*i > *(i + h))
            {
                std::swap(*i, *(i + h));
            }
        }

        // use next h down to 1 to perform sort.
        h = (h - 1) / 3;
    }
    */

    /*
    // version 2
    while (h >= 1)
    {
        for (auto i = first; i + h != last; i++)
        {
            // j-4 could out of iterator range
            for (auto j = i + h; j != first && *j < *(j - h); j = j - h)
            {
                std::swap(*j, *(j - h));
            }
        }

        // use next h down to 1 to perform sort.
        h = (h - 1) / 3;
    }
    */

    // version 3
    while (h >= 1)
    {
        for (auto i = first; i + h != last; i++)
        {
            // note distance could return negative, put smaller iter front
            for (auto j = i + h; std::distance(first, j) >= h && *j < *(j - h); j = j - h)
            {
                std::swap(*j, *(j - h));
            }
        }

        // use next h down to 1 to perform sort.
        h = (h - 1) / 3;
    }
}

