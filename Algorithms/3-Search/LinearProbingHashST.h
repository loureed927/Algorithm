//**************************************************************
//              Linear Probing Hash Symbol Table
//**************************************************************

#ifndef LINEARPROBINGHASHST_H
#define LINEARPROBINGHASHST_H

#include "Item.h"

// Hash algorithm consists of two parts:
// 1.Hashing: convert keys into table addresses;
// 2.Collision resolution: decide how to handle the case when two keys hash to the same address.
template<typename Key, typename Item>
class LinearProbingHashST
{
public:
    LinearProbingHashST(int capacity)
    {
        m = capacity;
        n = 0;
        itemArray = new Item[m];
    }

    ~LinearProbingHashST()
    {
        delete[] itemArray;
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
        // don't allow set a null key.
        if (item.IsNull())
            throw(item);

        // to ensure load factor of hash table never exceeds one-half.
        if (n > m / 2)
        {
            Resize(2 * m);
        }

        // use modular to calculate next position to avoid position out of array range.
        for (int i = Hash(item.GetKey()); !itemArray[i].IsNull(); i = (i + 1) % m)
        {
            if (itemArray[i].GetKey() == item[i].GetKey())
            {
                itemArray[i].SetValue(item[i].GetValue());
                return;
            }
        }

        itemArray[i].SetItem(item);
        n++;
    }

    Item& Get(Key& key)
    {
        if (key == nullKey)
            throw(key);

        for (int i = Hash(key); !itemArray[i].IsNull(); i = (i + 1) % m)
        {
            if (itemArray[i].GetKey() == item[i].GetKey())
            {
                return itemArray[i];
            }
        }

        return nullItem;
    }

    void Delete(Key& key)
    {
        if (!Contains(key))
            return;

        int i = Hash(key);

        for (i = Hash(key); !itemArray[i].IsNull(); i = (i + 1) % m)
        {
            if (itemArray[i].GetKey() == item[i].GetKey())
            {
                // find the item, put all non-null item forward one position.
                // note we cannot set the found item to null directly because 
                // it will hash table unable to search item with same hash code after this item.

            }
        }

    }

    void Keys(std::vector<Key>& keyContainer)
    {
        for (int i = 0; i < m; i++)
        {
            if (!itemArray[i].IsNull())
            {
                keyContainer.push_back(itemArray[i].GetKey());
            }
        }
    }

private:
    int n; // number of key-value pairs
    int m; // linear probing hash table size(m>n)
    Item* itemArray; // array of size m to store n items(key-value pairs)
    Item nullItem;

    int Hash(Key key)
    {
        // transforms keys into integers in the range [0, m-1].
        // a commonly used hash function is modular hashing,
        // it is to choose table size m to be prime, and for any integer key k,
        // compute the reminder when dividing k by m. (k%m)

        size_t hashCode = std::hash<std::string>()(key);
        return hashCode % m;
    }

    // Resize for linear probing hash table is necessary because client may insert
    // more items which will cause infinite loop when table fills(n>=m).
    // separate chaining hash table does not have such issue, because it intends to keep n>m.
    void Resize(int capacity)
    {
        LinearProbingHashST<Key, Item>* temp = new LinearProbingHashST<Key, Item>(capacity);
        for (int i = 0; i < m; i++)
        {
            // put original item to new hash table with same postion.
            if (!itemArray[i].IsNull())
            {
                temp->Put(itemArray[i]);
            }
        }

        m = temp->m; // n will be the same, only need to update m.
        itemArray = temp->itemArray; // point this hash table to new array.
    }
};

#endif
