//**************************************************************
//              bag
//**************************************************************

#ifndef BAG_H
#define BAG_H

#include <memory>

// Linked list based bag
template<typename T>
class LinkedListBag
{
public:
    LinkedListBag() :first(nullptr), num(0)
    {
    }

    ~LinkedListBag()
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

    void add(T item)
    {
        // insert new item afront.
        std::shared_ptr<Node> newItem = std::make_shared<Node>();
        newItem->elem = item;
        newItem->next = first;
        // update link header.
        first = newItem;
        num++;
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

