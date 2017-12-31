//**************************************************************
//                  Cycle Detection
//**************************************************************

#ifndef CYCLEDETECTION_H
#define CYCLEDETECTION_H

#include "Graph.h"

// A dfs application to support query: Is given graph acyclic?
// (Assumes no self-loops or parallel edges).
class CycleDetection
{
public:
    CycleDetection(Graph& g)
    {
        int vertices = g.Vertices();
        marked = new bool[vertices];

        for (int m = 0; m < vertices; m++)
        {
            marked[m] = false;
        }

        hasCycle = false;

        // start from vertex 0
        for (int m = 0; m < vertices && !HasCycle(); m++)
        {
            if (!marked[m])
            {
                dfs(g, m, m);
            }
        }
    }

    ~CycleDetection()
    {
        delete[] marked;
    }

    bool HasCycle()
    {
        return hasCycle;
    }

private:
    void dfs(Graph& g, int v, int w)
    {
        marked[v] = true;

        for (int a : g.AdjacentToVertex(v))
        {
            if (!marked[a])
            {
                dfs(g, a, v);
            }
            // to exclude self-loop and parallel edges.
            // e.g: edges
            // 0: 6 2 1 5
            // 6: 0 4
            // when dfs start from 0, we have parallel edges 0-6 and 6-0
            // after exclusion, all marked vertex revisited indicates graph is cyclic.
            else if (a != w)
            {
                hasCycle = true;
                return;
            }
        }
    }

    bool* marked;
    bool hasCycle;
};
#endif

