//**************************************************************
//                  Connected Components
//**************************************************************

#ifndef CONNECTEDCOMPONENTS_H
#define CONNECTEDCOMPONENTS_H

#include "Graph.h"

class ConnectedComponents
{
public:
    ConnectedComponents(Graph& g)
    {
        int vertices = g.Vertices();
        marked = new bool[vertices];
        id = new int[vertices];
        for (int m = 0; m < vertices; m++)
        {
            marked[m] = false;
            id[m] = 0;
        }

        count = 0;

        // start from vertex 0
        for (int m = 0; m < vertices; m++)
        {
            if (!marked[m])
            {
                dfs(g, m);
                count++;
            }
        }
    }

    ~ConnectedComponents()
    {
        delete[] marked;
        delete[] id;
    }

    // are vertex v and w connected?
    bool Connected(int v, int w)
    {
        // is v and w belong to same component?
        return Id(v) == Id(w);
    }

    // number of connected components.
    int Count()
    {
        return count;
    }

    // components identifier for vertex v.(between 0 and Count()-1)
    int Id(int v)
    {
        return id[v];
    }

private:
    void dfs(Graph& g, int v)
    {
        marked[v] = true;
        id[v] = count; // id starts from 0, so all connected vertices share same id.

        for (int a : g.AdjacentToVertex(v))
        {
            if (!marked[a])
            {
                dfs(g, a);
            }
        }
    }

    bool* marked;
    int* id; // component id for each vertex
    int count;
};

#endif
