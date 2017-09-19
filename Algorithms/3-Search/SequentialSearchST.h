//**************************************************************
//              SequentialSearch Symbol Table
//**************************************************************

#ifndef SEQUENTIALSEARCHST_H
#define SEQUENTIALSEARCHST_H

#include <memory>

struct intWrapper
{
    int value;

    intWrapper(int i)
    {
        value = i;
    }

    operator int() const
    {
        return value;
    }
};
typedef intWrapper index;


// Key and Value needs to be object in this solution, which is not applicable
// for the type could be c++ built-in type, like int...
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
        //// key type could be string... which cannot compare with nullptr.
        //// key must not be null.
        //if (key == nullptr)
        //    throw(key);

        // ensure no key in the table is associated with null.
        if (val == nullptr)
        {
            Delete(key);
            return;
        }

        // if key does not exist, put it the header of linked list.
        if (Get(key) == nullptr)
        {
            std::shared_ptr<Node> newfirst = std::make_shared<Node>(key, val, first);
            first = newfirst;
            num++;
        }
        else
        {
            // loop the linked list to find Node with input key, update its value then.
            // Get already loop the linked list, no need to loop again.
            for (std::shared_ptr<Node> i = first; i != nullptr; i = i->next)
            {
                if (i->key == key)
                {
                    i->val = val;
                }
            }
        }
    }

    Value Get(Key key)
    {
        //// key must not be null.
        //if (key == nullptr)
        //    throw(key);

        // loop the linked list to find Node with input key, return corresponding value.
        for (std::shared_ptr<Node> i = first; i != nullptr; i = i->next)
        {
            if (i->key == key)
            {
                return i->val;
            }
        }

        // return null if not found.
        // Note Value type could fail to cast to pointer
        return nullptr;
    }

    // use eager deletion here.
    // lazy deletion will put(key, null), and remove it later.
    void Delete(Key key)
    {
        //// key must not be null.
        //if (key == nullptr)
        //    throw(key);

        // loop the linked list to find Node with input key.
        for (std::shared_ptr<Node> i = first; i != nullptr; i = i->next)
        {
            std::shared_ptr<Node> deleteNode = i->next;
            if (deleteNode->key == key)
            {
                // remove it from linked list.
                i->next = deleteNode->next;
                num--;
            }
        }
    }

    bool Contains(Key key)
    {
        //// key must not be null.
        //if (key == nullptr)
        //    throw(key);

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

