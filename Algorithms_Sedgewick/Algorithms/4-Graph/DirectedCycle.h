//**************************************************************
//                  Directed Cycle
//**************************************************************

#ifndef DIRECTEDCYCLE_H
#define DIRECTEDCYCLE_H

#include <stack>
#include "Digraph.h"

class DirectedCycle
{
public:
    DirectedCycle(Digraph& g)
    {
        int vertices = g.Vertices();
        marked = new bool[vertices];
        edgeTo = new int[vertices];
        onStack = new bool[vertices];
        for (int m = 0; m < vertices; m++)
        {
            marked[m] = false;
            edgeTo[m] = 0;
            onStack[m] = false;
        }

        // start from vertex 0
        for (int m = 0; m < vertices; m++)
        {
            if (!marked[m])
            {
                dfs(g, m);
            }
        }
    }
    
    ~DirectedCycle()
    {
        delete[] marked;
        delete[] edgeTo;
        delete[] onStack;
    }

    // Does graph have a directed cycle?
    bool HasCycle()
    {
        return !cycle.empty();
    }

    // vertices on a cycle if existed.
    std::stack<int> Cycle()
    {
        return cycle;
    }

private:
    // Why CycleDetection for undirected graph cannot apply to directed graph???
    void dfs(Digraph& g, int v)
    {
        // to visit a vertex, marked it as having been visited.
        marked[v] = true;
        onStack[v] = true;

        for (int a : g.AdjacentToVertex(v))
        {
            if (HasCycle())
                return;

            // if adjacent vertex of v is not visited, continue with dfs.
            if (!marked[a])
            {
                edgeTo[a] = v;
                dfs(g, a);
            }
            // if adjacent vertex is already on callstack, then it is a cycle.
            else if (onStack[a])
            {
                // push the path to the cycle stack.
                for (int i = v; i != a; i = edgeTo[i])
                {
                    cycle.push(i);
                }

                cycle.push(a);
                cycle.push(v);
            }
        }

        onStack[v] = false;
    }

    bool* marked; // array of bool values to mark all of the vertices that are connected to the source or not.
    int* edgeTo; // last vertex on known path to this vertex.
    bool* onStack; // vertices on recursively call stack.
    stack<int> cycle; // vertices on a cycle.
};

#endif
