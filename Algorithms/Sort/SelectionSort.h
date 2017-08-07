

template<class RandomAccessIterator>
void SelectionSort(RandomAccessIterator first, RandomAccessIterator last)
{
    for (RandomAccessIterator i = first; i < last; ++i)
    {
		// find min index
		RandomAccessIterator min = i;
        for (RandomAccessIterator j = i + 1; j < last; ++j)
        {
			if (*min > *j)
				min = j;	
        }

		std::swap(*i, *min);
    }
}
