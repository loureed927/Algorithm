//**************************************************************
//          main test routine for test symbol table algorithms
//**************************************************************

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "BinarySearchST.h"
#include "SequentialSearchST.h"

using namespace std;

void SequentialSearchST_TestClient()
{
    SequentialSearchST<Key, Item> st;

    ifstream inputFile("tinyST.txt");
    string line, word;
    static int i = 0;

    // populate st.
    while (getline(inputFile, line))
    {
        istringstream stringIn(line);
        while (stringIn >> word)
        {
            Item it(word, i++);
            st.Put(it);
        }
    }

    // show st.
    std::vector<Key> keyContainer;
    st.Keys(keyContainer);

    cout << "sequential search symbol table items:" << endl;
    for (auto k : keyContainer)
    {
        cout << k << ' ' << st.Get(k).GetValue() << endl;
    }

    // test delete item from st.
    Key keyToDelete("X");
    st.Delete(keyToDelete);
    // output st again.
    keyContainer.clear();
    st.Keys(keyContainer);

    cout << "sequential search symbol table items after delete key:" << keyToDelete << endl;
    for (auto k : keyContainer)
    {
        cout << k << ' ' << st.Get(k).GetValue() << endl;
    }
}

void BinarySearchST_TestClient()
{
    BinarySearchST<Key, Item> st(20);

    ifstream inputFile("tinyST.txt");
    string line, word;
    static int i = 0;

    // populate st.
    while (getline(inputFile, line))
    {
        istringstream stringIn(line);
        while (stringIn >> word)
        {
            Item it(word, i++);
            st.Put(it);
        }
    }

    // show st.
    std::vector<Key> keyContainer;
    st.Keys(keyContainer);

    cout << "binary search symbol table items:" << endl;
    for (auto k : keyContainer)
    {
        cout << k << ' ' << st.Get(k).GetValue() << endl;
    }

    // test for ceiling and floor of specified key.
    Key temp("E");// key in st
    Key ceiling = st.Ceiling(temp);
    Key floor = st.Floor(temp);
    cout << "The ceiling key of key " << temp << " is " << ceiling << endl;
    cout << "The floor key of key " << temp << " is " << floor << endl;

    Key temp2("N");// key not in st
    Key ceiling2 = st.Ceiling(temp2);
    Key floor2 = st.Floor(temp2);
    cout << "The ceiling key of key " << temp2 << " is " << ceiling2 << endl;
    cout << "The floor key of key " << temp2 << " is " << floor2 << endl;

    // test delete item from st.
    Key keyToDelete("X");
    st.Delete(keyToDelete);
    // output st again.
    keyContainer.clear();
    st.Keys(keyContainer);

    cout << "binary search symbol table after delete key:" << keyToDelete << endl;
    for (auto k : keyContainer)
    {
        cout << k << ' ' << st.Get(k).GetValue() << endl;
    }
}

int main()
{
    //SequentialSearchST_TestClient();
    BinarySearchST_TestClient();
}

