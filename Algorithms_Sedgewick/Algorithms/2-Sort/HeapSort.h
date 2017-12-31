//**************************************************************
//          heap sort
//**************************************************************

template<class T>
void Sink(vector<T>& a, int k, int N)
{
    while (2*k <= N)
    {
        int child = 2*k;
        if (child < N && a[child] < a[child + 1])
        {
            child++;
        }

        if (a[k]>=a[child])
            break;

        std::swap(a[k], a[child]);
        k = child;
    }
}

template<class T>
void HeapSort(vector<T>& a)
{
    // heap sort has two phases:
    // 1. heap construction: reorganize the original array into a heap;
    // 2. sortdown, pull the items out of the heap in decreasing order to build sorted result.
    int N = a.size() - 1;
    for (int k = N / 2; k >= 1; k--)
    {
        Sink(a, k, N);
    }

    while (N > 1)
    {
        // place max element in the end of sorted heap.
        std::swap(a[1], a[N--]);
        Sink(a, 1, N);
    }
}

