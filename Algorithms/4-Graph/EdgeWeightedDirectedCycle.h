//**************************************************************
//                  Edge-Weighted Directed Cycle
//**************************************************************

#ifndef EDGEWEIGHTEDDIRECTEDCYCLE_H
#define EDGEWEIGHTEDDIRECTEDCYCLE_H

#include <stack>
#include "DirectedEdge.h"
#include "EdgeWeightedDigraph.h"

// same as DirectedCycle, extend for edge-weighted digraph.
class EdgeWeightedDirectedCycle
{
public:
    EdgeWeightedDirectedCycle(EdgeWeightedDigraph& g)
    {
        int vertices = g.Vertices();
        marked = new bool[vertices];
        edgeTo = new DirectedEdge[vertices];
        onStack = new bool[vertices];
        for (int m = 0; m < vertices; m++)
        {
            marked[m] = false;
            onStack[m] = false;
        }

        // start from vertex 0
        for (int m = 0; m < vertices; m++)
        {
            if (!marked[m])
            {
                dfs(g, m);
            }
        }
    }

    ~EdgeWeightedDirectedCycle()
    {
        delete[] marked;
        delete[] edgeTo;
        delete[] onStack;
    }

    // Does graph have a directed cycle?
    bool HasCycle()
    {
        return !cycle.empty();
    }

    // vertices on a cycle if existed.
    std::stack<DirectedEdge> Cycle()
    {
        return cycle;
    }

private:
    // Why CycleDetection for undirected graph cannot apply to directed graph???
    void dfs(EdgeWeightedDigraph& g, int v)
    {
        // to visit a vertex, marked it as having been visited.
        marked[v] = true;
        onStack[v] = true;

        for (auto e : g.AdjacentToVertex(v))
        {
            if (HasCycle())
                return;

            int vertexTo = e.To();

            if (!marked[vertexTo])
            {
                edgeTo[vertexTo] = e;
                dfs(g, vertexTo);
            }
            // if adjacent vertex is already on callstack, then it is a cycle.
            else if (onStack[vertexTo])
            {
                // push the path to the cycle stack.
                for (auto i = v; i != vertexTo; i = edgeTo[vertexTo].From())
                {
                    cycle.push(edgeTo[i]);
                }
                cycle.push(e);
            }
        }

        onStack[v] = false;
    }

    bool* marked; // array of bool values to mark all of the vertices that are connected to the source or not.
    DirectedEdge* edgeTo; // last edge on known path to this vertex.
    bool* onStack; // vertices on recursively call stack.
    stack<DirectedEdge> cycle; // edges on a cycle.
};

#endif
