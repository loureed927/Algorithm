//**************************************************************
//          main test routine for test fundamental data structures
//**************************************************************

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "Stack.h"

using namespace std;

int main()
{
    FixedCapacityStack<string> stack(100);
    ifstream inputFile("tobe.txt");
    string line, word;

    string strDash("-");

    while (getline(inputFile, line))
    {
        istringstream stringIn(line);
        while (stringIn >> word)
        {
            // if input string is not "-", then push string into stack.
            if (word != strDash)
            {
                stack.push(word);
            }
            else if (!stack.isEmpty())
            {
                cout << stack.pop() << ' ';
            }
        }
        cout << "(" << stack.size() << " left on stack)" << endl;
    }
}

