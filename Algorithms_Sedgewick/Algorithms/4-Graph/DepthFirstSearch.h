//**************************************************************
//                  Depth First Search
//**************************************************************

#ifndef DEPTHFIRSTSEARCH_H
#define DEPTHFIRSTSEARCH_H

#include "Graph.h"

class DepthFirstSearch
{
public:
    DepthFirstSearch(Graph& g, int s)
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
    // note we have to pass in reference to Graph, should not create local instance of Graph by dfs(Graph g, int v),
    // otherwise iterator of g will be invalid when return from recursively calling.
    void dfs(Graph& g, int v)
    {
        // to visit a vertex, marked it as having been visited.
        marked[v] = true;
        // adjacent unvisited vertex count for connected vertices.
        count++;

        for (int a : g.AdjacentToVertex(v))
        {
            // if adjacent vertex of v is not visited, continue with dfs.
            if (!marked[a])
            {
                dfs(g, a);
            }
        }
    }

    bool* marked; // array of bool values to mark all of the vertices that are connected to the source.
    int count;
};

#endif
