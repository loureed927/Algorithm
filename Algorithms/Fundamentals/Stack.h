//**************************************************************
//              stack
//**************************************************************

// Fixed Capacity Stack
template<typename T>
class FixedCapacityStack
{
public:
    FixedCapacityStack(int cap)
    {
        a = new T[cap];
    };

    ~FixedCapacityStack()
    {
        delete[] a;
    };

    bool isEmpty()
    {
        return num == 0;
    };

    int size()
    {
        return num;
    };

    void push(T item)
    {
        a[num++] = item;
    };

    T pop()
    {
        return a[--num];
    };

private:
    T* a;
    int num;
};

