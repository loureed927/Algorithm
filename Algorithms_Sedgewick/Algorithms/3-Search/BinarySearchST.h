//**************************************************************
//              BinarySearch Symbol Table
//**************************************************************

#ifndef BINARYSEARCHST_H
#define BINARYSEARCHST_H

#include <vector>
#include "Item.h"

// ordered array based binary search ST
template<typename Key, typename Item>
class BinarySearchST
{
public:
    BinarySearchST(int capacity) : num(0)
    {
        // fixed size array, not do resizing for simplicity.
        itemArray = new Item[capacity];
    }

    ~BinarySearchST()
    {
        delete[] itemArray;
    }

    void Put(Item& item)
    {
        if (item.IsNull())
            throw(item);

        int i = Rank(item.GetKey());
        // if item key is in st, then update its value.
        if (i < num && itemArray[i].GetKey() == item.GetKey())
        {
            itemArray[i].SetValue(item.GetValue());
        }
        else// otherwise insert it by order.
        {
            // for items in [i, num-1], need to move one position backwards.
            // considering keys[0, 1, 3], now insert item key is 2, which rank 2.
            // so j=3,i=2, need to move item[2] which is item[num-1] to item[num].
            // note the movement starts from last item, ends at item[i], which is the smallest j-1= (i+1)-1 =i.
            for (int j = num; j > i; j--)
            {
                itemArray[j] = itemArray[j - 1];
            }
            // put item in the right place.
            itemArray[i] = item;

            num++;
        }
    }

    Item& Get(Key& key)
    {
        if (key == nullKey)
            throw(key);

        int i = Rank(key);
        if (i < num && itemArray[i].GetKey() == key)
        {
            return itemArray[i];
        }
        else
        {
            return nullItem;
        }
    }

    void Delete(Key& key)
    {
        if (Get(key).IsNull())
            return;

        int index = Rank(key);
        // no need to consider if it is the last one.
        //// if the key is not the last one, move items after the key one position forward.
        //if (index < num - 1)
        //{
        //    for (int i = index; i < num; i++)
        //    {
        //        itemArray[i] = itemArray[i + 1];
        //    }
        //}

        //// set the last item to null.
        //itemArray[num-1] = nullItem;

        // Note if it is last key(index=num-1), this operation to move items will not be executed.
        for (int i = index; i < num - 1; i++)
        {
            itemArray[i] = itemArray[i + 1];
        }

        itemArray[num - 1] = nullItem;
        num--;
    }

    // Rank will return the number of keys smaller than given key.
    // so if given key is rank 0, then corresponding item is itemArray[0].
    // if given key is rank i, then corresponding item is itemArray[i].
    // the valid range of rank is [0, num-1] if key is in the array.
    // if the key is not in the array, the range will be [0, num].
    int Rank(Key& key)
    {
        if (key == nullKey)
            throw(key);

        // using recursive binary search.
        return RankRecursion(key, 0, num - 1);
        // using iterative binray search.
        //return RankIteration(key);
    }

    bool Contains(Key& key)
    {
        // this cannot work since != is not overloaded for class Item.
        // return Get(key) != nullItem
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
        return itemArray[0].GetKey();
    }

    Key& Max()
    {
        return itemArray[num-1].GetKey();
    }

    Item& Select(int k)
    {
        if (k < 0 || k >= num)
            throw(k);

        return itemArray[k];
    }

    // Returns the smallest key in this symbol table greater than or equal to given key.
    Key& Ceiling(Key& key)
    {
        //if (Get(key) == nullItem)
        //{
        //    return itemArray[Rank(key)].GetKey();
        //}
        //else
        //{
        //    return key;
        //}

        // solution from book is not well handled for rank(key)=num,
        // in that case, itemArray will be out of range.
        //return itemArray[Rank(key)].GetKey();

        if (key == nullKey)
            throw(key);

        int index = Rank(key);
        // if given key is not in the st, and every items in st is smaller than it, then it has no ceiling.
        if (index == num)
            return nullKey;
        else
            return itemArray[index].GetKey();
    }

    // Returns the largest key in this symbol table less than or equal to given key.
    Key& Floor(Key& key)
    {
        // this solution does not consider key less than item[0] does not have a floor.
        //if (Get(key) == nullItem)
        //{
        //    return itemArray[Rank(key)-1].GetKey();
        //}
        //else
        //{
        //    return key;
        //}

        if (key == nullKey)
            throw(key);

        int index = Rank(key);
        // if it is in the st
        if (index < num && itemArray[index].GetKey() == key)
        {
            return key;
        }
        else
        {
            if (index == 0)
            {
                return nullKey;
            }
            else
            {
                return itemArray[index - 1].GetKey();
            }
        }
    }

    // access vector contains all keys in ST.
    void Keys(std::vector<Key>& keyContainer)
    {
        return Keys(keyContainer, Min(), Max());
    }

    void Keys(std::vector<Key>& keyContainer, Key& lo, Key& hi)
    {
        for (int i = Rank(lo); i < Rank(hi); i++)
        {
            keyContainer.push_back(itemArray[i].GetKey());
        }
        if (Contains(hi))
        {
            keyContainer.push_back(hi);
        }
    }

private:
    Item nullItem;
    Item* itemArray;
    int num;

    int RankRecursion(Key& key, int lo, int hi)
    {
        if (lo > hi)
            return lo;

        int mid = lo + (hi - lo) / 2;

        if (key < itemArray[mid].GetKey())
        {
            return RankRecursion(key, lo, mid - 1);
        }
        else if (key > itemArray[mid].GetKey())
        {
            return RankRecursion(key, mid + 1, hi);
        }
        else
        {
            return mid;
        }
    }

    int RankIteration(Key& key)
    {
        int lo = 0;
        int hi = num - 1;

        while (lo <= hi)
        {
            int mid = lo + (hi - lo) / 2;
            if (key < itemArray[mid].GetKey())
            {
                hi = mid - 1;
            }
            else if (key > itemArray[mid].GetKey())
            {
                lo = mid + 1;
            }
            else
            {
                return mid;
            }
        }
    }
};

#endif
