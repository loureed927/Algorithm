//**************************************************************
//          quick sort
//**************************************************************
template<class T>
int Partition(vector<T>& t, int lo, int hi)
{
/*   Attempt one(failed to handle equal elements)
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

/*   Attempt two(failed to handle max partition element)
    // make postion j point to lo's element.
    int j = lo;

    int head = lo + 1;
    int tail = hi;

    while (head < tail)
    {
        // only increase head if its element smaller than partition element
        if (t[head] < t[j])
        {
            head++;
        }

        // only decrease tail if its element larger than partition element
        if (t[tail] > t[j])
        {
            tail--;
        }

        // elements equal to partition element also needs to be exchanged!!!(E C A I E)
        if (t[head] >= t[j] && t[tail] <= t[j])
        {
            std::swap(t[head++], t[tail--]);
        }
    }

    // do the last exchange
    // need to consider partition element is larger than all left and right scan. (E C A)
    std::swap(t[j], t[--head]);
    j = head;

    // t[j] is now at its final position.
    return j;
*/

/*   Attempt three(work)
    // make postion j point to lo's element.
    int j = lo;

    int head = lo + 1;
    int tail = hi;

    // head could out of range.
    if (head > tail)
        return j;

    while (head <= tail)
    {
        // only increase head if its element smaller than partition element
        if (t[head] < t[j] && t[tail] <= t[j])
        {
            head++;
        }
        // only decrease tail if its element larger than partition element
        else if (t[head] >= t[j] && t[tail] > t[j])
        {
            tail--;
        }
        else if (t[head] < t[j] && t[tail] >t[j])
        {
            head++;
            tail--;
        }
        // elements equal to partition element also needs to be exchanged!!!
        // e.g., (E C A I E), I>E from left scan and E=E from right scan,
        // if we don't stop at the E from right scan, it will leave as original position which is wrong.
        // what happens if (E C A B E)?? => (E C A B), j=5
        else if (t[head] >= t[j] && t[tail] <= t[j])
        {
            std::swap(t[head++], t[tail--]);
        }
    }

    // do the last exchange
    // need to consider partition element is larger than all left and right scan. (E C A)
    std::swap(t[j], t[--head]);
    j = head;

    // t[j] is now at its final position.
    return j;
*/

    // solution from book
    int head = lo;
    int j = hi + 1;// search j position from end of array.

    // t[lo] is partition item
    while (true)
    {
        // scan left, find element 'head' larger than(or equal to) partition element.
        while (t[++head] < t[lo])
        {
            if (head == hi)
                break;
        }
        // scan right, find element 'j' less than(or equal to) partition element.
        while (t[--j] > t[lo])
        {
            if (j == lo)
                break;
        }

        // if found element 'head' exceed 'j' position, no need to exchange. 
        if (head >= j)
            break;

        std::swap(t[head], t[j]);
    }

    std::swap(t[lo], t[j]);

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

/*
    // Attempt two(work)
    int j = Partition(t, lo, hi);

    if (j<lo ||j>hi)
        return;

    QuickSort(t, lo, j - 1);
    QuickSort(t, j + 1, hi);
*/

    // solution from book.
    if (lo >= hi)
        return;

    int j = Partition(t, lo, hi);
    QuickSort(t, lo, j - 1);
    QuickSort(t, j + 1, hi);
}

