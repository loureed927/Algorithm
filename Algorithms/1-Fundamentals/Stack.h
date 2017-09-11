//**************************************************************
//              stack
//**************************************************************

#ifndef STACK_H
#define STACK_H

#include <memory>

// Fixed Capacity Stack
template<typename T>
class FixedCapacityStack
{
public:
    FixedCapacityStack(int cap)
    {
        a = new T[cap];
    }

    ~FixedCapacityStack()
    {
        delete[] a;
    }

    bool isEmpty()
    {
        return num == 0;
    }

    int size()
    {
        return num;
    }

    void push(T item)
    {
        // push should check whether array is already full, omit here for simplicity.
        a[num++] = item;
    }

    T pop()
    {
        return a[--num];
    }

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
        length = 1;
        a = new T[length];
        num = 0;
    }

    ~ResizingArrayStack()
    {
        delete[] a;
    }

    bool isEmpty()
    {
        return num == 0;
    }

    int size()
    {
        return num;
    }

    void push(T item)
    {
        // if array is full, allocate double size.
        if (length == num)
        {
            resize(2 * num);
        }

        a[num++] = item;
    }

    T pop()
    {
        T t = a[--num];

        if (num > 0 && num == length / 4)
        {
            resize(length / 2);
        }

        return t;
    }

private:

    void resize(int max)
    {
        T* temp = new T[max];
        for (int i = 0; i < num; i++)
        {
            temp[i] = a[i];
        }

        // need to free original memory of array, and point it to new memory "temp".
        delete[] a;

        a = temp;
        length = max;
    }

    T* a;
    int length; // array length
    int num;    // element number
};


// Linked list based stack
// Attempt 1.
// there are 2 issues of this implementation:
// 1. Does not delete orphan node object;
// 2. loop link to get size, an alternative is to keep a int to record link size when push&pop.
/*
template<typename T>
class LinkedListStack
{
public:
    LinkedListStack()
    {
        first = nullptr;
    }

    ~LinkedListStack()
    {

    }

    bool isEmpty()
    {
        return first == nullptr;
    }

    int size()
    {
        // loop the link to calculate size.
        int num = 0;
        for (Node* i = first; i != nullptr; i = i->next)
        {
            num++;
        }
        return num;
    }

    void push(T item)
    {
        // insert new item afront.
        Node* newItem = new Node;
        newItem->elem = item;
        newItem->next = first;
        // update link header.
        first = newItem;
    }

    T pop()
    {
        T deletedItem = first->elem;
        // remove item afront.
        first = first->next;
        return deletedItem;
    }

private:

    struct Node
    {
        T elem;
        Node* next;
    }

    Node* first; // link header
};
*/

// Attempt 2: using smart pointer for Node object and bookkeeping link size.
// Note here using shared_ptr instead of unique_ptr since we need copy operation.
template<typename T>
class LinkedListStack
{
public:
    LinkedListStack() :first(nullptr), num(0)
    {
    }

    ~LinkedListStack()
    {
    }

    bool isEmpty()
    {
        return first == nullptr;
    }

    int size()
    {
        return num;
    }

    void push(T item)
    {
        // insert new item afront.
        std::shared_ptr<Node> newItem = std::make_shared<Node>();
        newItem->elem = item;
        newItem->next = first;
        // update link header.
        first = newItem;
        num++;
    }

    T pop()
    {
        if (first == nullptr)
            throw(first);

        T deletedItem = first->elem;
        // remove item afront.
        first = first->next;
        num--;
        return deletedItem;
    }

private:

    struct Node
    {
        T elem;
        std::shared_ptr<Node> next;
    };

    std::shared_ptr<Node> first; // link header
    int num;
};

#endif
