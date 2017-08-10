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
}

