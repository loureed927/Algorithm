//**************************************************************
//                  Directed Depth First Search
//**************************************************************

#ifndef DIRECTEDDFS_H
#define DIRECTEDDFS_H

#include <vector>
#include "Digraph.h"

// this is similar as undirected graph DFS, adding solution to multiple-source reachability.
class DirectedDFS
{
public:
    // find vertices in graph that are reachable from s.
    DirectedDFS(Digraph& g, int s)
    {
        int vertices = g.Vertices();
        marked = new bool[vertices];
        for (int m = 0; m < vertices; m++)
        {
            marked[m] = false;
        }

        dfs(g, s);
    }

    // find vertices in graph that are reachable from sources.
    DirectedDFS(Digraph& g, vector<int>& sources)
    {
        int vertices = g.Vertices();
        marked = new bool[vertices];
        for (int m = 0; m < vertices; m++)
        {
            marked[m] = false;
        }

        for (auto s : sources)
        {
            if (!marked[s])
            {
                dfs(g, s);
            }
        }
    }

    ~DirectedDFS()
    {
        delete[] marked;
    }

    // is v reachable from s/sources?
    bool Marked(int v)
    {
        return marked[v];
    }

private:
    void dfs(Digraph& g, int v)
    {
        // to visit a vertex, marked it as having been visited.
        marked[v] = true;

        for (int a : g.AdjacentToVertex(v))
        {
            // if adjacent vertex of v is not visited, continue with dfs.
            if (!marked[a])
            {
                dfs(g, a);
            }
        }
    }

    bool* marked; // array of bool values to mark all of the vertices that are connected to the source or not.
};

#endif
