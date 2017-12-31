//**************************************************************
//         DAG Longest Paths
//**************************************************************

#ifndef ACYCLICLP_H
#define ACYCLICLP_H

#include <vector>
#include <stack>
#include "DirectedEdge.h"
#include "EdgeWeightedDigraph.h"
#include "TopologicalSort.h"
#include "..\2-Sort\PriorityQueue.h"

// solve the single-source longest-paths problem in edge-weighted DAG (negative edge weight allowed).
class AcyclicLP
{
public:
    AcyclicLP(EdgeWeightedDigraph& g, int s)
    {
        int vertices = g.Vertices();
        numVectices = vertices;

        edgeTo = new DirectedEdge[vertices];
        distTo = new double[vertices];
        for (int m = 0; m < vertices; m++)
        {
            if (m == s)
            {
                // the distance of source to source is zero.
                distTo[m] = 0.0;
            }
            else
            {
                // define initial value for other distTo[] as negative infinity.
                distTo[m] = std::numeric_limits<double>::min();
            }
        }

        // relax vertices in topological order, there is no need for IndexMinPQ since all vertices are only visited once.
        TopologicalSort ts(g);
        assert(ts.IsDAG());

        vector<int> topoOrder(ts.Order());
        for (auto o : topoOrder)
        {
            Relax(g, o);
        }
    }

    ~AcyclicLP()
    {
        delete[] edgeTo;
        delete[] distTo;
    }

    // distance from s to v, positive infinity if no path.
    double DistTo(int v)
    {
        return distTo[v];
    }

    // has path from s to v or not?
    bool HasPathTo(int v)
    {
        return DistTo(v) > std::numeric_limits<double>::min();
    }

    // path from s to v.
    stack<DirectedEdge> PathTo(int v)
    {
        std::stack<DirectedEdge> lpt;
        if (!HasPathTo(v))
            return lpt;

        for (auto e = edgeTo[v]; !e.IsNull(); e = edgeTo[e.From()])
        {
            lpt.push(e);
        }

        return lpt;
    }

private:

    void Relax(EdgeWeightedDigraph& g, int v)
    {
        for (auto e : g.AdjacentToVertex(v))
        {
            int w = e.To();
            double distBeforeRelax = distTo[v] + e.Weight();
            if (distBeforeRelax > distTo[w])
            {
                distTo[w] = distBeforeRelax;
                edgeTo[w] = e;
            }
        }
    }

    DirectedEdge* edgeTo;
    double* distTo;
    int numVectices;
};

#endif
