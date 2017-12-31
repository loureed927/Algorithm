//**************************************************************
//                  Degrees Of Separation
//**************************************************************

#ifndef DEGREESOFSEPARATION_H
#define DEGREESOFSEPARATION_H

#include <iostream>
#include "SymbolGraph.h"
#include "BreadthFirstPaths.h"

// A symbol graph and bfs(breadth first path) application to
// find shortest path in graph.
// it takes source vertex from argument and takes queries from standard input,
// then prints a shortest path from the source to the query vertex.
class DegreesOfSeparation
{
public:
    static void CalculateDOS(string& filename, string& delimiter, string& source)
    {
        SymbolGraph sg(filename, delimiter);
        Graph* g = sg.GetGraph();

        if (!sg.Contains(source))
        {
            cout << source << "not in the database." << endl;
        }

        int s = sg.Index(source);
        BreadthFirstPaths bfp(*g, s);

        string destination;
        while (getline(cin, destination))
        {
            if (sg.Contains(destination))
            {
                int d = sg.Index(destination);
                cout << "shortest path from " << source << " to " << destination << ":" << endl;

                if (bfp.HasPathTo(d))
                {
                    std::stack<int> pathStack(bfp.PathTo(d));

                    // get path vertex from start by pop the stack.
                    while (!pathStack.empty())
                    {
                        int pathNode = pathStack.top();
                        cout << sg.Name(pathNode) << endl;
                        pathStack.pop();
                    }
                }
                else
                {
                    cout << "source and destination are not connected." << endl;
                }
                cout << endl;

                cout << "input destination vertex name:";
            }
            else if (strcmp(destination.c_str(), "Q") == 0)
            {
                // press Q to exit input.
                break;
            }
            else
            {
                cout << "Cannot find any input string in symbol graph." << endl;
                cout << "Please input destination vertex name again:";
            }
        }
    }

private:
    DegreesOfSeparation() = delete;
    ~DegreesOfSeparation() = delete;
    DegreesOfSeparation(const DegreesOfSeparation&) = delete;
    DegreesOfSeparation& operator=(const DegreesOfSeparation&) = delete;
};

#endif
