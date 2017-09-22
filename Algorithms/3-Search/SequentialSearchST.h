//**************************************************************
//              SequentialSearch Symbol Table
//**************************************************************

#ifndef SEQUENTIALSEARCHST_H
#define SEQUENTIALSEARCHST_H

#include <string>
#include <memory>
#include <vector>

// the class definition for Items that are small records consisting of string key and integer value.
typedef std::string Key;
typedef int Value;

static Key nullKey("");

class Item
{
    // need to put private member afront.
private:
    Key key;
    Value val;

public:
    // Item is initialized to be null.
    Item()
    {
        key = nullKey;
    }

    // easy to construct for client
    Item(Key k, Value v) :key(k), val(v)
    {
    }

    const Key GetKey()
    {
        return key;
    }

    const Value GetValue()
    {
        return val;
    }

    void SetValue(Value v)
    {
        val = v;
    }

    bool IsNull()
    {
        return key == nullKey;
    }
};

// unordered linked list based sequential search ST
template<typename Key, typename Item>
class SequentialSearchST
{
public:
    SequentialSearchST() :first(nullptr), num(0)
    {
    }

    ~SequentialSearchST()
    {
    }

    void Put(Item& item)
    {
        // item to be insert should not be null.
        if (item.IsNull())
            throw(item);

        // loop the linked list to find Node with same key of input item, update its value then.
        for (std::shared_ptr<Node> i = first; i != nullptr; i = i->next)
        {
            if (i->item.GetKey() == item.GetKey())
            {
                i->item.SetValue(item.GetValue());
                return;
            }
        }

        // if not found, insert to header.
        first = std::make_shared<Node>(item, first);
        num++;
    }

    Item& Get(Key& key)
    {
        // loop the linked list to find Node with input key, return corresponding item.
        for (std::shared_ptr<Node> i = first; i != nullptr; i = i->next)
        {
            if (i->item.GetKey() == key)
            {
                return i->item;
            }
        }

        // return null if not found.
        return nullItem;
    }

    // use eager deletion here.
    void Delete(Key& key)
    {
        if (key == nullKey)
            return;

        Delete(first, key);

        // this way of delete has issue: if first item is to be deleted, the first node is invalid.
        //// cannot delete a null item.
        //if (item.IsNull())
        //    throw(item);

        //// loop the linked list to find Node with same key of input item.
        //for (std::shared_ptr<Node> i = first; i != nullptr; i = i->next)
        //{
        //    std::shared_ptr<Node> deleteNode = i->next;
        //    if (deleteNode->item.GetKey() == item.GetKey())
        //    {
        //        // remove it from linked list.
        //        i->next = deleteNode->next;
        //        num--;
        //    }
        //}
    }

    bool Contains(Key& key)
    {
        return Get(key) != nullItem;
    }

    bool IsEmpty()
    {
        return Size() == 0;
    }

    int Size()
    {
        return num;
    }

    // access vector contains all keys in ST.
    void Keys(std::vector<Key>& keyContainer)
    {
        for (std::shared_ptr<Node> i = first; i != nullptr; i = i->next)
        {
            keyContainer.push_back(i->item.GetKey());
        }
    }

private:
    Item nullItem;
    int num;

    struct Node
    {
        Item item;
        std::shared_ptr<Node> next;

        Node(Item it, std::shared_ptr<Node> nt)
        {
            item = it;
            next = nt;
        }
    };

    std::shared_ptr<Node> first;

    std::shared_ptr<Node> Delete(std::shared_ptr<Node> node, Key& key)
    {
        if (node == nullptr)
            return nullptr;

        // if found, return node next to the deleted one.
        if (node->item.GetKey() == key)
        {
            num--;
            return node->next;
        }

        // recursively find the node and delete it
        node->next = Delete(node->next, key);
        return node;
    }
};

/*
// use solution from book cannot deal with generic key/value type very well.

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
*/

#endif

