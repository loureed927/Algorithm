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

    ~FixedCapacityStack(){};

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
        
    };

    T pop()
    {

    };

private:
    T* a;
    int num;
};

