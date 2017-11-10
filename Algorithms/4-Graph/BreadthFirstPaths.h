//**************************************************************
//                  Breadth First Paths
//**************************************************************

#ifndef BREADTHFIRSTPATHS_H
#define BREADTHFIRSTPATHS_H

#include <stack>
#include "Graph.h"

// to find single source shortest paths.
class BreadthFirstPaths
{
public:
    BreadthFirstPaths(Graph& g, int s)
    {
        int vertices = g.Vertices();
        marked = new bool[vertices];
        edgeTo = new int[vertices];
        this->s = s;

        for (int m = 0; m < vertices; m++)
        {
            marked[m] = false;
            edgeTo[m] = s;
        }

        bfs(g, s);
    }

    ~BreadthFirstPaths()
    {
        delete[] marked;
        delete[] edgeTo;
    }

    // same as Marked from DepthFirstSearch to indicate v is connected to s or not.
    bool HasPathTo(int v)
    {
        return marked[v];
    }

    // same as DepthFirstPath. and paths has the property that no other such path from s to v has fewer edges.
    std::stack<int> PathTo(int v)
    {
        std::stack<int> path;
        if (!HasPathTo(v))
            return path;

        for (int x = v; x != s; x = edgeTo[x])
        {
            path.push(x);
        }
        path.push(s);

        return path;
    }

private:
    void bfs(Graph& g, int v)
    {
        // to visit a vertex, marked it as having been visited.
        marked[v] = true;

        for (int a : g.AdjacentToVertex(v))
        {
            // if adjacent vertex of v is not visited, continue with dfs.
            if (!marked[a])
            {
                marked[a] = true;
                edgeTo[a] = v; // store the last vertex on the path.
            }
        }

        for (int a : g.AdjacentToVertex(v))
        {
            bfs(g, a);
        }
    }

    bool* marked; // array of bool values to mark all of the vertices that are connected to the source.
    int* edgeTo; // last vertex on known path to this vertex.
    int s; // source
};

#endif
