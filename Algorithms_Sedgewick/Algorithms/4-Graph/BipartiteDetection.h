//**************************************************************
//                  Bipartite Detection
//**************************************************************

#ifndef BIPARTITEDETECTION_H
#define BIPARTITEDETECTION_H

#include "Graph.h"

// A dfs application to support query: Is given graph bipartite?
// (Also known as two-colorability -- Can the vertices of a given graph
// be assigned one of two colors in such a way that no edge connects vertices
// of the same color?).
class BipartiteDetection
{
public:
    BipartiteDetection(Graph& g)
    {
        int vertices = g.Vertices();
        marked = new bool[vertices];
        color = new bool[vertices];

        for (int m = 0; m < vertices; m++)
        {
            marked[m] = false;
            color[m] = false;
        }

        isBipartite = true;

        // start from vertex 0
        for (int m = 0; m < vertices; m++)
        {
            if (!marked[m])
            {
                dfs(g, m);
            }
        }
    }

    ~BipartiteDetection()
    {
        delete[] marked;
    }

    bool IsBipartite()
    {
        return isBipartite;
    }

private:
    void dfs(Graph& g, int v)
    {
        marked[v] = true;

        for (int a : g.AdjacentToVertex(v))
        {
            if (!marked[a])
            {
                // give all unmarked vertices connected to current vertex anther color.
                color[a] = !color[v];
                dfs(g, a);
            }
            // if graph is acyclic, then it always can be two colorable??
            else
            {
                // if it is marked vertex, then it has been assigned a color.
                // test whether it is different from v's color or not.
                // if it is different, then still two-colorable.
                if (color[a] == color[v])
                    isBipartite = false;
            }
        }
    }

    bool* marked;
    bool* color; // color for each vertex.
    bool isBipartite;
};

#endif
