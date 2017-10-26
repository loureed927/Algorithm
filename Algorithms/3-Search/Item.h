//**************************************************************
//              Item class
//**************************************************************

#ifndef ITEM_H
#define ITEM_H

#include <string>

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

    Key& GetKey()
    {
        return key;
    }

    void SetKey(Key& k)
    {
        key = k;
    }

    Value& GetValue()
    {
        return val;
    }

    void SetValue(Value& v)
    {
        val = v;
    }

    void SetItem(Item& item)
    {
        key = item.GetKey();
        val = item.GetValue();
    }

    bool IsNull()
    {
        return key == nullKey;
    }
};

#endif

