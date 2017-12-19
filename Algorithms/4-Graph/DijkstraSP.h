//**************************************************************
//         Dijkstra's Algorithm For Shortest Paths
//**************************************************************

#ifndef DIJKSTRASP_H
#define DIJKSTRASP_H

#include <vector>
#include <stack>
#include "DirectedEdge.h"
#include "EdgeWeightedDigraph.h"
#include "..\2-Sort\PriorityQueue.h"

class DijkstraSP
{
public:
    DijkstraSP(EdgeWeightedDigraph& g, int s)
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

        pq = new IndexMinPQ<double>(vertices);

        // relax non-tree vertex with lowest distTo[], and add it to the shortest paths tree(SPT).
        // continue until all vertices are on the SPT or non-tree vertex has infinite distTo.
        Relax(g, s);

        while (!pq->IsEmpty())
        {
            // get vertex in mst, and remove it from pq.
            int VertexToBeAdded = pq->DeleteMin();

            Relax(g, VertexToBeAdded);
        }
    }

    ~DijkstraSP()
    {
        delete[] edgeTo;
        delete[] distTo;
        delete pq;
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

        for (auto e = edgeTo[v]; e.IsNull(); e = edgeTo[e.From()])
        {
            spt.push(e);
        }

        return spt;
    }

private:
    // Edge Relaxation:
    // Relax edge v->w means to test whether the best known way from s to w is to go from s to v,
    // then take the edge from v to w.
    // How to test? shortest path s->w throug v is distTo[v] + weight(edge(v->w)), if this value
    // is no smaller than distTo[w], then this edge(v->w) is ineligible. Otherwise thie edge(v->w)
    // leads to a shorter path to w, thus needs to update edgeTo[w] and distTo[w], which called
    // successful relaxation.
    // Vertex Relaxation:
    // Relax vertex v means to relax all the edges pointing from v, to find a shorter path than 
    // the best known so far to the vertex pointing from v.
    // Note if distTo[v] is finite and vertex w pointing to has an infinite distTo[w], then edge v->w
    // is eligible and will be added to edgeTo[w] if relaxed.
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

                // add the vertex to priority queue after relax.
                if (pq->Contains(w))
                {
                    pq->Change(w, distTo[w]);
                }
                else
                {
                    pq->Insert(w, distTo[w]);
                }
            }
        }
    }

    DirectedEdge* edgeTo;       // edgeTo[v] is the edge connects v to its parent in the tree,
                                // also it is the last edge on a shortest path from s to v.
    double* distTo;             // length of the shortest path from s to v.
    IndexMinPQ<double>* pq;     // vertices that are candidates for being the next to be relaxed.
    int numVectices;            // total number of vertices, also size for edgeTo and distTo.
};

#endif
