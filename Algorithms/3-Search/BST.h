//**************************************************************
//              Binary Search Tree
//**************************************************************

#ifndef BST_H
#define BST_H

#include "Item.h"

// binary search tree
template<typename Key, typename Item>
class BST
{
public:
    BST() : num(0)
    {

    }

    ~BST()
    {

    }

    void Put(Item& item)
    {
        if (item.IsNull())
            throw(item);

    }

    Item& Get(Key& key)
    {
        if (key == nullKey)
            throw(key);
    }

    void Delete(Key& key)
    {
        if (Get(key).IsNull())
            return;
    }

    // Rank will return the number of keys smaller than given key.
    int Rank(Key& key)
    {
        if (key == nullKey)
            throw(key);

    }

    bool Contains(Key& key)
    {
        return !Get(key).IsNull();
    }

    bool IsEmpty()
    {
        return Size() == 0;
    }

    int Size()
    {
        return num;
    }

    Key& Min()
    {

    }

    Key& Max()
    {

    }

    Item& Select(int k)
    {

    }

    // Returns the smallest key in this symbol table greater than or equal to given key.
    Key& Ceiling(Key& key)
    {
        if (key == nullKey)
            throw(key);
    }

    // Returns the largest key in this symbol table less than or equal to given key.
    Key& Floor(Key& key)
    {
        if (key == nullKey)
            throw(key);

    }

    // access vector contains all keys in ST.
    void Keys(std::vector<Key>& keyContainer)
    {

    }

    void Keys(std::vector<Key>& keyContainer, Key& lo, Key& hi)
    {

    }

private:
    Item nullItem;

    int num;
};

#endif
