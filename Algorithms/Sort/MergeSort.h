//**************************************************************
//          shell sort
//**************************************************************

using namespace std;
// Abstract in-place merge
template<class T>
void Merge(vector<T>& t, int lo, int mid, int hi)
{
    //merge subarrays t[lo,mid] and t[mid, hi] into a single ordered array.
    vector<T> aux;

    // copy original elements from t to aux
    for (int k = lo; k <= hi; k++)
    {
        aux.push_back(t[k]);
    }

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
    int mid = (lo + hi) / 2;
    while (mid <= hi)
    {
        // sort first and second half of top array, down to the minimal array.
        MergeSortTD(t, lo, hi / 2);
        MergeSortTD(t, mid / 2 + 1, hi);
    }

    // Now we have sorted half arrays, do the merge
    Merge(t, lo, mid, hi);
}

void MergeSortBU()
{

}

