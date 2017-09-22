//**************************************************************
//              BinarySearch Symbol Table
//**************************************************************

#ifndef BINARYSEARCHST_H
#define BINARYSEARCHST_H

#include <string>
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

        Item it = Get(Item.GetKey());
        // if item key is in st, then update its value.
        if (it != nullItem)
        {
            it.SetValue(item.GetValue());
        }
        else// otherwise insert it by order.
        {
            int i = Rank(item.GetKey());

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

    }

    // Rank will return the number of keys smaller than given key.
    // so if given key is rank 0, then corresponding item is itemArray[0].
    // if given key is rank i, then corresponding item is itemArray[i].
    // the valid range of rank is [0, num-1].
    int Rank(Key& key)
    {

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

    Key& Min()
    {

    }

    Key& Max()
    {

    }

    Item& Select(int k)
    {

    }

    Key& Ceiling(Key& key)
    {

    }

    Key& Floor(Key& key)
    {

    }

    // access vector contains all keys in ST.
    void Keys(std::vector<Key>& keyContainer)
    {

    }

private:
    Item nullItem;
    Item* itemArray;
    int num;
};

#endif
