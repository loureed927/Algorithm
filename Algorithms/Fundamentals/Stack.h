//**************************************************************
//              stack
//**************************************************************

#ifndef STACK_H
#define STACK_H

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
        // push should check whether array is already full, omit here for simplicity.
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

// Resizing Array Stack
template<typename T>
class ResizingArrayStack
{
public:
    ResizingArrayStack()
    {
        a = new T[1];
        num = 0;
    };

    ~ResizingArrayStack()
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
        // if array is full, allocate double size.
        if (a->size() == num)
        {
            resize(2 * num);
        }

        a[num++] = item;
    };

    T pop()
    {
        T t = a[--num];

        if (num == a->size() / 4)
        {
            resize(a->size() / 2);
        }

        return t;
    };

private:

    void resize(int max)
    {
        T* temp = new T[max];
        for (int i = 0; i < num; i++)
        {
            temp[i] = a[i];
        }

        a = temp;
    };

    T* a;
    int num;
};


#endif
