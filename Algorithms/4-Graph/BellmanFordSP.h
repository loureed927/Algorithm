//**************************************************************
//         Bellman-Ford's Algorithm For Shortest Paths
//            (General edge-weighted digraph)
//**************************************************************

#ifndef BELLMANFORDSP_H
#define BELLMANFORDSP_H

#include <vector>
#include <queue>
#include <stack>
#include "DirectedEdge.h"
#include "EdgeWeightedDigraph.h"
#include "EdgeWeightedDirectedCycle.h"

using namespace std;

// Bellman-Ford algorithm computes the shortest path tree in edge-weighted digraph
// from vertex s, or finds a negative cost cycle reachable from s.
class BellmanFordSP
{
public:
    BellmanFordSP(EdgeWeightedDigraph& g, int s)
    {
        int vertices = g.Vertices();
        numVectices = vertices;
        cost = 0;

        edgeTo = new DirectedEdge[vertices];
        distTo = new double[vertices];
        onQueue = new bool[vertices];
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

            onQueue[m] = false;
        }

        que.push(s);

        while (!que.empty() && !HasNegativeCycle())
        {
            int VertexToBeAdded = que.front();
            que.pop();
            onQueue[VertexToBeAdded] = false;
            Relax(g, VertexToBeAdded);
        }
    }

    ~BellmanFordSP()
    {
        delete[] edgeTo;
        delete[] distTo;
        delete[] onQueue;
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

    bool HasNegativeCycle()
    {
        return !cycle.empty();
    }

    stack<DirectedEdge> NegativeCycle()
    {
        return cycle;
    }

private:

    void Relax(EdgeWeightedDigraph& g, int v)
    {
        for (auto e : g.AdjacentToVertex(v))
        {
            int w = e.To();
            double distBeforeRelax = distTo[v] + e.Weight();
            if (distBeforeRelax < distTo[w])
            {
                // edge v->w is eligible, relax it
                distTo[w] = distBeforeRelax;
                edgeTo[w] = e;

                // if distTo[] of vertex changed in this pass, the edges it pointing to 
                // can change other vertices' distTo.
                if (!onQueue[w])
                {
                    que.push(w);
                    onQueue[w] = true;
                }
            }

            if (++cost % numVectices == 0)
            {
                FindNegativeCycle();
                if (HasNegativeCycle())
                    return;
            }
        }
    }

    void FindNegativeCycle()
    {
        // build edge-weighted digraph from edgeTo[] and look for cycle in this subgraph.
        EdgeWeightedDigraph subGraph(numVectices);
        for (int i = 0; i < numVectices; i++)
        {
            if (!edgeTo[i].IsNull())
            {
                subGraph.AddEdge(edgeTo[i]);
            }
        }

        EdgeWeightedDirectedCycle dc(subGraph);
        cycle = dc.Cycle();
    }

    DirectedEdge* edgeTo;
    double* distTo;
    bool* onQueue;              // is this vertex on the queue?
    queue<int> que;             // vertices that are candidates for being the next to be relaxed.
    int numVectices;            // total number of vertices, also size for edgeTo and distTo.
    int cost;                   // number of calls to Relax().
    stack<DirectedEdge> cycle; // negative cycle in edge[].
};

#endif
