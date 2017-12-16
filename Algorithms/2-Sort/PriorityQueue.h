//**************************************************************
//          priority queue
//**************************************************************

// binary heap based max priority queue.
template<typename T>
class MaxPQ
{
public:
    MaxPQ(int max) :n(0)
    {
        pq = new T[max + 1];
    }

    ~MaxPQ()
    {
        delete[] pq;
    }

    void Insert(T& t)
    {
        pq[++n] = t;
        swim(n);
    }

    T& Max()
    {
        return pq[1];
    }

    T DeleteMax()
    {
        T max = pq[1];
        std::swap(pq[1], pq[n--]);

        // now we have N-1 elements, pq[N] unused. since we decrease N already, make pq[N+1] null.
        pq[n + 1] = nullptr;

        sink(1);
        return max;
    }

    bool IsEmpty()
    {
        return n == 0;
    }

    int Size()
    {
        return n;
    }

private:

    void Swim(int k)
    {
        // if child is larger than parent, swim child to parent level.
        while (k > 1 && pq[k] > pq[k / 2])
        {
            std::swap(pq[k], pq[k / 2]);
            k = k / 2;
        }
    }

    void Sink(int k)
    {
        // if parent is less than child, sink parent to child level.
        //while (k < N)
        //{
        //    if (pq[k]>=pq[2k] || pq[k]>=pq[2k+1])
        //        break;

        //    if (pq[k] < pq[2k])
        //    {
        //        std::swap(pq[k], pq[2k]);
        //        k = 2k;
        //    }
        //    else if (pq[k] < pq[2k + 1])
        //    {
        //        std::swap(pq[k], pq[2k + 1]);
        //        k = 2k + 1;
        //    }
        //}

        while (2*k <= n)
        {
            // find the larger one of two children.
            // this is to simplify the process of compare k and child.
            // no need to compare with two children, we only compare k with larger one.
            int child = 2*k;
            if (child < n && pq[child] < pq[child + 1])
            {
                child++;
            }

            // if element k is larger(equal) than the larger child, then no need to exchange,
            // the k is at its position in MaxPQ.
            if (pq[k] >= pq[child])
                break;

            std::swap(pq[k], pq[child]);

            k = child;

        }
    }

    T* pq; // pq is a fixed size array.
    int n; // all elements are stored in pq[1...n], pq[0] unused.
};


// index minimum priority queue.
// for easily access element in the MinPQ, use index to manipulate items.
template<typename T>
class IndexMinPQ
{
public:
    IndexMinPQ(int max) :n(0)
    {
        pq = new int[max + 1];
        qp = new int[max + 1];
        Item = new T[max + 1];

        for (int i = 0; i < max; i++)
        {
            // assume all items are not in the pq, so qp[] = -1.
            qp[i] = -1;
        }
    }

    ~IndexMinPQ()
    {
        delete[] pq;
        delete[] qp;
        delete[] Item;
    }

    // is index k on the priority queue(associated with any item)?
    bool Contains(int k)
    {
        return qp[k] != -1;
    }

    // insert item associated with index k.
    void Insert(int k, T& t)
    {
        if (Contains(k))
            return;

        // n is array index, pq[n] stores the index of item which is input k.
        n++; // firstly increase the n, since we start the heap from 1.
        pq[n] = k;
        qp[k] = n;
        Item[k] = t;
        Swim(n); // it actually reheaplify the index priority queue according the comparison of items. No need to sink since it is the last item already at the bottom.
    }

    // change the item associated with index k.
    void Change(int k, T& t)
    {
        // index k should be in the heap.
        if (!Contains(k))
            throw(k);

        Item[k] = t;
        // reheaplify.
        Swim(qp[k]);
        Sink(qp[k]);
    }

    // delete the item associated with index k.
    void Delete(int k)
    {
        // index k should be in the heap.
        if (!Contains(k))
            throw(k);

        Exchange(qp[k], n--); // exchange with the input index(needs to be convert to array index in pq) with last item.

        // reheaplify from exchanged position.
        Swim[qp[k]]; // why we need swim here since the item should be the max one which should only need sink???
        Sink(qp[k]);

        // now we have n-1 elements, pq[n] unused. since we decrease N already, make pq[n+1] corresponding item as null.
        pq[n + 1] = -1;
        qp[k] = -1;
        //Item[k] = nullptr;
    }

    // minimum item.
    T& Min()
    {
        assert(n != 0);
        return Item[pq[1]];
    }

    // index of minimum item.
    int MinIndex()
    {
        assert(n != 0);
        return pq[1];
    }

    // delete minimum item and return its index.
    int DeleteMin()
    {
        int index = MinIndex();
        Exchange(1, n--); // exchange with the min with last item.

        // since last item in at the top, sink to reheaplify.
        Sink(1);

        // now we have n-1 elements, pq[n] unused. since we decrease N already, make pq[n+1] corresponding item as null.
        pq[n + 1] = -1; 
        qp[index] = -1;
        //Item[index] = nullptr;

        return index;
    }

    bool IsEmpty()
    {
        return n == 0;
    }

    int Size()
    {
        return n;
    }

private:
    // utility function
    bool Greater(int i, int j)
    {
        return Item[pq[i]] > Item[pq[j]];
    }

    void Exchange(int i, int j)
    {
        std::swap(pq[i], pq[j]);
        std::swap(qp[pq[i]], qp[pq[j]]);
    }

    // counterpart of swim/sink version of MaxPQ.
    // swim the input item to correct position at MinPQ.
    void Swim(int k)
    {
        // if child is less than parent, swim child to parent level.
        while (k > 1 && Greater(k / 2, k))
        {
            Exchange(k, k / 2);
            k = k / 2;
        }
    }

    void Sink(int k)
    {
        while (2*k <= n)
        {
            // find the smaller one of two children.
            // this is to simplify the process of compare k and child.
            // no need to compare with two children, we only compare k with smaller one.
            int child = 2*k;
            if (child < n && Greater(child, child + 1))
            {
                child++;
            }

            // if element k is less(equal) than the smaller child, then no need to exchange,
            // the k is at its position in MinPQ.
            if (!Greater(k, child))
                break;

            Exchange(k, child);

            k = child;
        }
    }

    int* pq; // binary heap using 1-based indexing. item index array sorted from minimum item.
    int* qp; // inversion of pq. item index -> array index in pq.
    T* Item; // item associated with index.

    int n; // all elements are stored in pq[1...N], pq[0] unused.
};


