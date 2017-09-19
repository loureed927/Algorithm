//**************************************************************
//          main test routine for test symbol table algorithms
//**************************************************************

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "SequentialSearchST.h"

using namespace std;

int main()
{
    SequentialSearchST<string, index*> st;

    ifstream inputFile("tinyST.txt");
    string line, word;
    static int i = 0;

    while (getline(inputFile, line))
    {
        istringstream stringIn(line);
        while (stringIn >> word)
        {
            index* val = new index(i);
            st.Put(word, val);
            i++;
        }
    }
}

