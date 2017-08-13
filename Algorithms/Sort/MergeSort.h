//**************************************************************
//          shell sort
//**************************************************************

// Abstract in-place merge
template<class T>
void MergeSort(vector<T>& t, int lo, int mid, int hi)
{
    //merge subarrays t[lo,mid] and t[mid, hi] into a single ordered array.
    vector<T> aux;
    aux.reserve(t.size());

    // copy original elements from t to aux
    aux.insert(t.begin(), t.end());

    // merge two subarrays into one
    for (int i = 0; i <= hi; i++)
    {
        if (aux[i]<aux[mid+1])
    }
}

