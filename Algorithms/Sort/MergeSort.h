//**************************************************************
//          shell sort
//**************************************************************

using namespace std;
// Abstract in-place merge
template<class T>
void Merge(vector<T>& t, int lo, int mid, int hi)
{
    ////merge subarrays t[lo,mid] and t[mid, hi] into a single ordered array.
    //vector<T> aux;

    //// copy original elements from t to aux
    //for (int k = lo; k <= hi; k++)
    //{
    //    aux.push_back(t[k]);
    //}

    ////merge subarrays t[lo,mid] and t[mid, hi] into a single ordered array.
    //vector<T> aux;
    //aux.reserve(t.size());

    //// copy original elements from t to aux
    //// copy vector cannot use operator =
    //// Note we have allocate size of t for aux, and copy element needed to correct index.
    //for (int k = lo; k <= hi; k++)
    //{
    //    aux[k] = t[k];
    //}

    vector<T> aux(t);

    // merge two subarrays into one
    // Note for syntax does not support define values of multiple type
    for (int i = lo, j = mid + 1, k = lo; k <= hi; k++)
    {
        // consider two conditions that first or second subarray has been cycled to end before the other finished.
        if (i > mid)
            t[k] = aux[j++];
        else if (j > hi)
            t[k] = aux[i++];
        else if (aux[i] <= aux[j])
            t[k] = aux[i++];
        else
            t[k] = aux[j++];
    }
}

template<class T>
void MergeSortTD(vector<T>& t, int lo, int hi)
{
    /*
    // Attempt one:
    // this implementation will lead endless loop
    // trace::
    // MergeSortTD(t, 0, 5)
    //  MergeSortTD(t, 0, 2)
    //   MergeSortTD(t, 0, 1)
    //    Merge(t, 0, 0, 1)
    //   MergeSortTD(t, 1, 2)
    //    Merge(t, 1, 1, 2)
    //  MergeSortTD(t, 0, 2) since lo=0, hi=2
    //  endless loop
    int mid = (lo + hi) / 2;
    while (lo + 1 != hi)
    {
        // sort first and second half of top array, down to the minimal array.
        MergeSortTD(t, lo, hi / 2);
        MergeSortTD(t, mid / 2 + 1, hi);
    }

    // Now we have sorted half arrays, do the merge
    Merge(t, lo, mid, hi);
    */

    int mid = (lo + hi) / 2;

    while (lo + 1 < hi)
    {
        // sort first and second half of top array, down to the minimal array.
        MergeSortTD(t, lo, mid);
        MergeSortTD(t, mid + 1, hi);

        // when lower level recursive ended, how to back to higher level?
    }

    // Now we have sorted half arrays, do the merge
    Merge(t, lo, mid, hi);
}

void MergeSortBU()
{

}

