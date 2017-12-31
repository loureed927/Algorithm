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

        // For the given digraph G, use DepthFirstOrder to compute reverse postorder of its reverse graph G(R).
        // Run DFS on G with this order, and all vertices reached on a call to recursive dfs() are in a strongly component.
        // proof:
        // 1. every vertex v that is strongly connected to s is reached by dfs(G,s) in the constructor(not in recursion?).
        //    we have path s->v, if v is not reached by dfs(G,s), then v must have been previously marked.
        //    since we also have v->s, then s would be marked during previous dfs(G,v), then dfs(G,s) will not be called in constructor. Contradiction.
        // 2. every vertex v reached by dfs(G,s) in the constructor is strongly connected to s.
        //    there is a path s->v, so need to prove v->s in G, equivent to s->v in G(R).
        //    during dfs in G(R), the reverse postorder will come to: dfs(G, v) must be done before dfs(G, s) during dfs of G(R).???
        DepthFirstOrder dfo(g.Reverse());
        stack<int> reversePostOrder = dfo.ReversePostOrder();
        while (!reversePostOrder.empty())
        {
            int m = reversePostOrder.top();

            if (!marked[m])
            {
                dfs(g, m);
                count++;
            }

            reversePostOrder.pop();
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
