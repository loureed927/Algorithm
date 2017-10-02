//**************************************************************
//          main test routine for test symbol table algorithms
//**************************************************************

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "BinarySearchST.h"
#include "SequentialSearchST.h"
#include "BST.h"

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

    // test for range output of st
    keyContainer.clear();
    Key start("B"), end("N");
    st.Keys(keyContainer, start, end);
    cout << "binary search symbol table between " << start << " and " << end << ":" << endl;
    for (auto k : keyContainer)
    {
        cout << k << ' ' << st.Get(k).GetValue() << endl;
    }
}

void BST_TestClient()
{
    BST<Key, Item> st;

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

    cout << "BST items:" << endl;
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

    // test for select and rank
    int k = 1;
    Key selectKey = st.Select(k).GetKey();
    cout << "The key of rank " << k << " is " << selectKey << endl;

    Key rankKey("B");
    int rank = st.Rank(rankKey);
    cout << "The rank of key " << rankKey << " is " << rank << endl;

    // test for range output of st
    keyContainer.clear();
    Key start("F"), end("T");
    st.Keys(keyContainer, start, end);
    cout << "BST between " << start << " and " << end << ":" << endl;
    for (auto k : keyContainer)
    {
        cout << k << ' ' << st.Get(k).GetValue() << endl;
    }

    // test delete item from st.
    Key minKey = st.Min();
    st.DeleteMin();
    // output st again.
    keyContainer.clear();
    st.Keys(keyContainer);

    cout << "BST after delete min key:" << minKey << endl;
    for (auto k : keyContainer)
    {
        cout << k << ' ' << st.Get(k).GetValue() << endl;
    }

    Key maxKey = st.Max();
    st.DeleteMax();
    // output st again.
    keyContainer.clear();
    st.Keys(keyContainer);

    cout << "BST after delete max key:" << maxKey << endl;
    for (auto k : keyContainer)
    {
        cout << k << ' ' << st.Get(k).GetValue() << endl;
    }

    Key keyToDelete("E");
    st.Delete(keyToDelete);
    // output st again.
    keyContainer.clear();
    st.Keys(keyContainer);

    cout << "BST after delete key:" << keyToDelete << endl;
    for (auto k : keyContainer)
    {
        cout << k << ' ' << st.Get(k).GetValue() << endl;
    }
}

int main()
{
    //SequentialSearchST_TestClient();
    //BinarySearchST_TestClient();
    BST_TestClient();
}

