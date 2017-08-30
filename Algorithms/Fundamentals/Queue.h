//**************************************************************
//              queue
//**************************************************************

#ifndef QUEUE_H
#define QUEUE_H

#include <memory>

// Linked list based queue
template<typename T>
class LinkedListQueue
{
public:
    LinkedListQueue() :first(nullptr), last(first), num(0)
    {
    }

    ~LinkedListQueue()
    {
    }

    bool isEmpty()
    {
        return last == nullptr;
    }

    int size()
    {
        return num;
    }

    void enqueue(T item)
    {
        std::shared_ptr<Node> newItem = std::make_shared<Node>();
        newItem->elem = item;
        newItem->next = nullptr;
        // update link tail.
        if (last != nullptr)
            last->next = newItem;
        last = newItem;
        num++;
        if (num == 1)
            first = last;
    }

    T dequeue()
    {
        if (first == nullptr)
            throw(first);

        T deletedItem = first->elem;
        // remove item afront.
        first = first->next;
        num--;
        if (num == 1)
            first = last;
        return deletedItem;
    }

private:

    struct Node
    {
        T elem;
        std::shared_ptr<Node> next;
    };

    std::shared_ptr<Node> first;
    std::shared_ptr<Node> last;
    int num;
};

#endif

