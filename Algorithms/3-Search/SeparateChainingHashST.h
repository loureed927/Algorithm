//**************************************************************
//              Separate Chaining Hash Symbol Table
//**************************************************************

#ifndef SEPARATECHAININGHASHST_H
#define SEPARATECHAININGHASHST_H

#include <memory>
#include "Item.h"
#include "SequentialSearchST.h"

template<typename Key, typename Item>
class SeparateChainingHashST
{
public:
    SeparateChainingHashST()
    {
        this(997);
    }

    SeparateChainingHashST(int m)
    {
        st = new SequentialSearchST[m];
        this->m = m;
        for (int i = 0; i < m; i++)
        {
            st[i] = new SequentialSearchST;
        }
    }

    bool IsEmpty()
    {
        return Size() == 0;
    }

    int Size()
    {
        return n;
    }

    bool Contains(Key& key)
    {
        return !Get(key).IsNull();
    }

    void Put(Item& item)
    {
        return st[Hash(item.GetKey())]->Put(item);
    }

    Item& Get(Key& key)
    {
        return st[Hash(key)]->Get(key);
    }

    void Delete(Key& key)
    {
        st[Hash(key)]->Delete(key);
    }

    void Keys(std::vector<Key>& keyContainer)
    {

    }

private:
    int n; // number of key-value pairs
    int m; // hash table size
    std::shared_ptr<SequentialSearchST<Key, Item>> st; // hash table, array of sequential search ST with same hash code

    int Hash(Key key)
    {

    }
};

#endif
