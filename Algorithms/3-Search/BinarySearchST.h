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


    }

    Item& Get(Key& key)
    {

    }

    void Delete(Key& key)
    {

    }

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
