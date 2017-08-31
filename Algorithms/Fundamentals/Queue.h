//**************************************************************
//              queue
//**************************************************************

#ifndef QUEUE_H
#define QUEUE_H

#include <memory>

// Linked list based queue
/*
// Attempt1: work
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
*/

template<typename T>
class LinkedListQueue
{
public:
    LinkedListQueue() :first(nullptr), last(nullptr), num(0)
    {
    }

    ~LinkedListQueue()
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

    void enqueue(T item)
    {
        // Add item to the end of the list.
        std::shared_ptr<Node> oldLast = last;
        last = std::make_shared<Node>();
        last->elem = item;
        last->next = nullptr;

        // isEmpty uses first == nullptr to check list empty or not, should not use last == nullptr,
        // since for first enqueue to empty list, last is not nullptr here.
        // first is not changed after first enqueue, last will be changed everytime enqueue.
        if (isEmpty())
            first = last;
        else
            oldLast->next = last;

        num++;
    }

    T dequeue()
    {
        if (first == nullptr)
            throw(first);

        // Remove item from beginning of the list.
        T deletedItem = first->elem;
        first = first->next;

        // if only one item left in list, dequeue will make first == nullptr, then isEmpty is valid.
        // need to update last now since it still reference dequeued node.
        if (isEmpty())
            last = nullptr;

        num--;

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

