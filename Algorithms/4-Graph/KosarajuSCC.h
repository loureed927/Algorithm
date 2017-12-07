//**************************************************************
//                  Strongly Connected Components
//**************************************************************

#ifndef KOSARAJUSCC_H
#define KOSARAJUSCC_H

#include "Digraph.h"
#include "DepthFirstOrder.h"

class KosarajuSCC
{
public:
    KosarajuSCC(Digraph& g)
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

        DepthFirstOrder dfo(g.Reverse());
        for (auto m : dfo.ReversePostOrder())
        {
            if (!marked[m])
            {
                dfs(g, m);
                count++;
            }
        }
    }

    ~KosarajuSCC()
    {
        delete[] marked;
        delete[] id;
    }

    // are vertex v and w strongly connected?
    bool StronglyConnected(int v, int w)
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
    void dfs(Digraph& g, int v)
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
