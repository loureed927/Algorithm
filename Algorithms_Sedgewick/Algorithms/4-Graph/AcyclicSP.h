//**************************************************************
//         DAG Shortest Paths
//**************************************************************

#ifndef ACYCLICSP_H
#define ACYCLICSP_H

#include <vector>
#include <stack>
#include "DirectedEdge.h"
#include "EdgeWeightedDigraph.h"
#include "TopologicalSort.h"
#include "..\2-Sort\PriorityQueue.h"

// solve the single-source shortest-paths problem in edge-weighted DAG (negative edge weight allowed).
class AcyclicSP
{
public:
    AcyclicSP(EdgeWeightedDigraph& g, int s)
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
                // define initial value for other distTo[] as positive infinity.
                distTo[m] = std::numeric_limits<double>::max();
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

    ~AcyclicSP()
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
        return DistTo(v) < std::numeric_limits<double>::max();
    }

    // path from s to v.
    stack<DirectedEdge> PathTo(int v)
    {
        std::stack<DirectedEdge> spt;
        if (!HasPathTo(v))
            return spt;

        for (auto e = edgeTo[v]; !e.IsNull(); e = edgeTo[e.From()])
        {
            spt.push(e);
        }

        return spt;
    }

private:
    // same as relax in DijkstraSP algorithm.
    void Relax(EdgeWeightedDigraph& g, int v)
    {
        for (auto e : g.AdjacentToVertex(v))
        {
            int w = e.To();
            double distBeforeRelax = distTo[v] + e.Weight();
            if (distBeforeRelax < distTo[w])
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
