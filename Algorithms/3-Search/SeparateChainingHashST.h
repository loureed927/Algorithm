//**************************************************************
//              Separate Chaining Hash Symbol Table
//**************************************************************

#ifndef SEPARATECHAININGHASHST_H
#define SEPARATECHAININGHASHST_H

#include "Item.h"
#include "SequentialSearchST.h"

// Hash algorithm consists of two parts:
// 1.Hashing: convert keys into table addresses;
// 2.Collision resolution: decide how to handle the case when two keys hash to the same address.
template<typename Key, typename Item>
class SeparateChainingHashST
{
public:
    SeparateChainingHashST()
    {
        SeparateChainingHashST(997);
    }

    SeparateChainingHashST(int m)
    {
        st = (SequentialSearchST<Key, Item>*) new SequentialSearchST<Key, Item>[m];
        this->m = m;
        //for (int i = 0; i < m; i++)
        //{
        //    st[i] = (SequentialSearchST<Key, Item>)new SequentialSearchST<Key, Item>();
        //}
    }

    ~SeparateChainingHashST()
    {
        delete[] st;
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
        return st[Hash(item.GetKey())].Put(item);
    }

    Item& Get(Key& key)
    {
        return st[Hash(key)].Get(key);
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
    SequentialSearchST<Key, Item>* st; // hash table, array of sequential search ST with same hash code

    int Hash(Key key)
    {
        // transforms keys into integers in the range [0, m-1].
        // a commonly used hash function is modular hashing,
        // it is to choose table size m to be prime, and for any integer key k,
        // compute the reminder when dividing k by m. (k%m)

        int hashCode = std::hash<std::string>()(key);
        return hashCode % m;
    }
};

#endif
