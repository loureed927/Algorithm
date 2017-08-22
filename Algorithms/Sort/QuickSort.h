//**************************************************************
//          merge sort
//**************************************************************
template<class T>
int Partition(vector<T>& t, int lo, int hi)
{
/*   Attempt one(failed to handle equal keys)
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
    return j
*/

/*   Attempt two(failed to handle max partition key)
    // make postion j point to lo's element.
    int j = lo;

    int head = lo + 1;
    int tail = hi;

    while (head < tail)
    {
        // only increase head if its key smaller than partition key
        if (t[head] < t[j])
        {
            head++;
        }

        // only decrease tail if its key larger than partition key
        if (t[tail] > t[j])
        {
            tail--;
        }

        // keys equal to partition key also needs to be exchanged!!!(E C A I E)
        if (t[head] >= t[j] && t[tail] <= t[j])
        {
            std::swap(t[head++], t[tail--]);
        }
    }

    // do the last exchange
    // need to consider partition key is larger than all left and right scan. (E C A)
    std::swap(t[j], t[--head]);
    j = head;

    // t[j] is now at its final position.
    return j;
*/

    // make postion j point to lo's element.
    int j = lo;

    int head = lo + 1;
    int tail = hi;

    // head could out of range.
    if (head > tail)
        return j;

    while (head <= tail)
    {
        // only increase head if its key smaller than partition key
        if (t[head] < t[j] && t[tail] <= t[j])
        {
            head++;
        }
        // only decrease tail if its key larger than partition key
        else if (t[head] >= t[j] && t[tail] > t[j])
        {
            tail--;
        }
        else if (t[head] < t[j] && t[tail] >t[j])
        {
            head++;
            tail--;
        }
        // keys equal to partition key also needs to be exchanged!!!(E C A I E)
        else if (t[head] >= t[j] && t[tail] <= t[j])
        {
            std::swap(t[head++], t[tail--]);
        }
    }

    // do the last exchange
    // need to consider partition key is larger than all left and right scan. (E C A)
    std::swap(t[j], t[--head]);
    j = head;

    // t[j] is now at its final position.
    return j;

}

template<class T>
void QuickSort(vector<T>& t, int lo, int hi)
{
/*
    // Attempt one
    int j = Partition(t, lo, hi);

    if (j <= lo || j >= hi)
        return;

    QuickSort(t, lo, j - 1);
    QuickSort(t, j + 1, hi);
*/

    int j = Partition(t, lo, hi);

    if (j<lo ||j>hi)
        return;

    QuickSort(t, lo, j - 1);
    QuickSort(t, j + 1, hi);
}

