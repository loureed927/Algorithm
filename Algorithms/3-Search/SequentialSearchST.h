//**************************************************************
//              SequentialSearch Symbol Table
//**************************************************************

#ifndef SEQUENTIALSEARCHST_H
#define SEQUENTIALSEARCHST_H

#include <memory>

template<typename Key, typename Value>
class SequentialSearchST
{
public:
    SequentialSearchST() :first(nullptr), num(0)
    {

    }

    ~SequentialSearchST()
    {

    }

    void Put(Key key, Value val)
    {
        // key type could be int... which cannot convert with pointer.
        // key must not be null.
        if (key == nullptr)
            throw(key);

        // ensure no key in the table is associated with null.
        if ((void*)val == nullptr)
        {
            Delete(key);
            return;
        }

        // if key does not exist, put it the header of linked list.
        if ((void*)Get(key) == nullptr)
        {
            std::shared_ptr<Node> newfirst = std::make_shared<Node>(key, val, first);
            first = newfirst;
            num++;
        }
        else
        {
            // loop the linked list to find Node with input key, update its value then.
            for (std::shared_ptr<Node> i = first; i != nullptr && i->key == key; i = i->next)
            {
                i->val = val;
            }
        }
    }

    Value Get(Key key)
    {
        // key must not be null.
        if (key == nullptr)
            throw(key);

        // loop the linked list to find Node with input key, return corresponding value.
        for (std::shared_ptr<Node> i = first; i != nullptr && i->key == key; i = i->next)
        {
            return i->val;
        }

        // return null if not found.
        // Note Value type could fail to cast to pointer
        return nullptr;
    }

    // use eager deletion here.
    // lazy deletion will put(key, null), and remove it later.
    void Delete(Key key)
    {
        // key must not be null.
        if (key == nullptr)
            throw(key);

        // loop the linked list to find Node with input key.
        for (std::shared_ptr<Node> i = first; i != nullptr; i = i->next)
        {
            std::shared_ptr<Node> deleteNode = i->next;
            if (deleteNode->key == key)
            {
                // remove it from linked list.
                i->next = deleteNode->next;
                deleteNode->key = nullptr;
                deleteNode->val = nullptr;
                deleteNode->next = nullptr;
                num--;
            }
        }
    }

    bool Contains(Key key)
    {
        // key must not be null.
        if (key == nullptr)
            throw(key);

        return Get(key) != nullptr;
    }

    bool IsEmpty()
    {
        return Size() == 0;
    }

    int Size()
    {
        return num;
    }

private:
    // linked-list node
    class Node
    {
    public:
        Node(Key& key, Value& val, std::shared_ptr<Node> next) : key(key), val(val)
        {
            this->next = next;
        }

        // make values public to ST class.
        Key key;
        Value val;
        std::shared_ptr<Node> next;
    };

    std::shared_ptr<Node> first;
    int num;
};

#endif

