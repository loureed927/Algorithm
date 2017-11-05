//**************************************************************
//                  Depth First Search
//**************************************************************

#ifndef DEPTHFIRSTSEARCH_H
#define DEPTHFIRSTSEARCH_H

#include "Graph.h"

class DepthFirstSearch
{
public:
    DepthFirstSearch(Graph g, int s)
    {
        int vertices = g.Vertices();
        marked = new bool[vertices];
        for (int m = 0; m < vertices; m++)
        {
            marked[m] = false;
        }

        dfs(g, s);
    }

    ~DepthFirstSearch()
    {
        delete[] marked;
    }

    // is w connected to s?
    bool Marked(int w)
    {
        return marked[w];
    }

    // how many vertices are connected to s?
    int Count()
    {
        return count;
    }

private:
    void dfs(Graph g, int v)
    {
        // to visit a vertex, marked it as having been visited.
        marked[v] = true;
        for (int a : g.AdjacentToVertex(v))
        {
            // if adjacent vertex of v is not visited, continue with dfs.
            if (!marked[a])
            {
                // adjacent unvisited vertex count for connected vertices.
                count++;
                dfs(g, a);
            }
            else
            {
                return;
            }
        }
    }

    bool* marked; // array of bool values to mark all of the vertices that are connected to the source.
    int count;
};

#endif
