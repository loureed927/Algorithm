//**************************************************************
//          merge sort
//**************************************************************
template<class T>
int Partition(vector<T>& t, int lo, int hi)
{
    // make postion j point to lo's element.
    int j = lo;

    int head = lo;
    int tail = hi;

    while (head < tail)
    {
        if (t[head] <= t[j])
        {
            head++;
        }

        if (t[tail] >= t[j])
        {
            tail--;
        }

        if (t[head] > t[j] && t[tail] < t[j])
        {
            std::swap(t[head++], t[tail--]);
        }
    }

    // do the last exchange
    std::swap(t[j], t[--head]);
    j = head;

    // t[j] is now at its final postion.
    return j;
}

template<class T>
void QuickSort(vector<T>& t, int lo, int hi)
{
    int j = Partition(t, lo, hi);
    while (j != lo)
    {
        Partition(t, lo, j-1);
        Partition(t, j+1, hi);
    }
}

