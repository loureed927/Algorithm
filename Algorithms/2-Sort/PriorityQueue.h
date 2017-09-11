//**************************************************************
//          priority queue
//**************************************************************

// binary heap based max priority queue.
template<typename T>
class MaxPQ
{
public:
    MaxPQ(int max) :N(0)
    {
        pq = new T[max + 1];
    }

    ~MaxPQ()
    {
        delete[] pq;
    }

    void Insert(T t)
    {
        pq[++N] = t;
        swim(N);
    }

    T Max()
    {
        return pq[1];
    }

    T DeleteMax()
    {
        T max = pq[1];
        std::swap(pq[1], pq[N--]);

        // now we have N-1 elements, pq[N] unused. since we decrease N already, make pq[N+1] null.
        pq[N + 1] = nullptr;

        sink(1);
        return max;
    }

    bool IsEmpty()
    {
        return N == 0;
    }

    int Size()
    {
        return N;
    }

private:

    void swim(int k)
    {
        // if child is larger than parent, swim child to parent level.
        while (k > 1 && pq[k] > pq[k / 2])
        {
            std::swap(pq[k], pq[k / 2]);
            k = k / 2;
        }
    }

    void sink(int k)
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

        while (2k <= N)
        {
            // find the larger one of two children.
            // this is to simplify the process of compare k and child.
            // no need to compare with two children, we only compare k with larger one.
            int child = 2k;
            if (child < N && pq[child] < pq[child + 1])
            {
                child++;
            }

            // if element k is larger(equal) than the larger child, then no need to exchange,
            // the k is at its position.
            if (pq[k] >= pq[child])
                break;

            std::swap(pq[k], pq[child]);

            k = child;

        }
    }

    T* pq; // pq is a fixed size array.
    int N; // all elements are stored in pq[1...N], pq[0] unused.
};


