//**************************************************************
//          main test routine for test fundamental data structures
//**************************************************************

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>

#include "Stack.h"
#include "Queue.h"
#include "Bag.h"

using namespace std;

int main()
{
/*Test for stack
    //FixedCapacityStack<string> stack(100);
    //ResizingArrayStack<string> stack;
    LinkedListStack<string> stack;

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
*/

    /*test for queue*/
    LinkedListQueue<string> queue;

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
                queue.enqueue(word);
            }
            else if (!queue.isEmpty())
            {
                cout << queue.dequeue() << ' ';
            }
        }
        cout << "(" << queue.size() << " left on queue)" << endl;
    }
}

