//**************************************************************
//                  Depth First Paths
//**************************************************************

#ifndef DEPTHFIRSTPATHS_H
#define DEPTHFIRSTPATHS_H

#include <stack>
#include "Graph.h"

class DepthFirstPaths
{
public:
    DepthFirstPaths(Graph& g, int s)
    {
        int vertices = g.Vertices();
        marked = new bool[vertices];
        edgeTo = new int[vertices];
        this->s = s;

        for (int m = 0; m < vertices; m++)
        {
            marked[m] = false;
        }

        dfs(g, s);
    }

    ~DepthFirstPaths()
    {
        delete[] marked;
        delete[] edgeTo;
    }

    // same as Marked from DepthFirstSearch to indicate v is connected to s or not.
    bool HasPathTo(int v)
    {
        return marked[v];
    }

    // return path from s to v, could be empty.
    std::stack<int> PathTo(int v)
    {
        std::stack<int> path;
        int lastVertex = edgeTo[v];

        while (lastVertex != s)
        {
            path.push(lastVertex);
            lastVertex = edgeTo[lastVertex];
        }

        path.push(s);

        return path;
    }

private:
    // note we have to pass in reference to Graph, should not create local instance of Graph by dfs(Graph g, int v),
    // otherwise iterator of g will be invalid when return from recursively calling.
    void dfs(Graph& g, int v)
    {
        // to visit a vertex, marked it as having been visited.
        marked[v] = true;

        for (int a : g.AdjacentToVertex(v))
        {
            // if adjacent vertex of v is not visited, continue with dfs.
            if (!marked[a])
            {
                edgeTo[a] = v; // store the last vertex on the path.
                dfs(g, a);
            }
        }
    }

    bool* marked; // array of bool values to mark all of the vertices that are connected to the source.
    int* edgeTo; // last vertex on known path to this vertex.
    int s; // source
};

#endif
