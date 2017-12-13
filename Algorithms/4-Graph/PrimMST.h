//**************************************************************
//         Prim's Algorithm For Minimum Spanning Trees(MST)
//**************************************************************

#ifndef PRIMMST_H
#define PRIMMST_H

#include <vector>
#include <queue>
#include "Edge.h"
#include "EdgeWeightedGraph.h"

using namespace std;

class LazyPrimMST
{
public:
    LazyPrimMST(EdgeWeightedGraph& g)
    {
        int vertices = g.Vertices();
        marked = new bool[vertices];
        for (int m = 0; m < vertices; m++)
        {
            marked[m] = false;
        }

        // start from vertex 0.
        Visit(g, 0);

        while (!pq.empty())
        {
            Edge& e = pq.top();
            int v = e.Either();
            int w = e.Other(v);
            // if the edge is already in the MST, then delete it from pq.
            if (marked[v] && marked[w])
            {
                pq.pop();
                continue;
            }

            // add edge to MST.
            mst.push(e);
            pq.pop();

            // add vertex to MST.
            if (!marked[v])
            {
                Visit(g, v);
            }
            else if (!marked[w])
            {
                Visit(g, w);
            }
        }
    }

    ~LazyPrimMST()
    {
        delete[] marked;
    }

    // all of the MST edges.
    queue<Edge> Edges()
    {
        return mst;
    }

    // weight of MST.
    double Weight()
    {
        bool weight = 0.0;
        for (auto e : mst)
        {
            weight += e.Weight();
        }
        return weight;
    }

private:
    // put a vertex on the MST, marking it as visited and then put all of its incident edges
    // that are not ineligible onto the priority queue, thus ensure that the priority queue
    // contains the crossing edges from tree vertices to non-tree vertices.
    void Visit(EdgeWeightedGraph& g, int v)
    {
        marked[v] = true;

        for (auto e : g.AdjacentToVertex(v))
        {
            // if adjacent vertex is already in the MST which is marked, then no need to add the edge to priority queue.
            if (!marked[e.Other(v)])
            {
                pq.push(e);
            }
        }
    }

    bool* marked; // array of whether the vertex is on the MST.
                  // the reason why we need mark vertex on the MST is we cannot 
                  // know an edge is on the MST directly.
    queue<Edge> mst; // MST edges.
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq; // crossing (and ineligible) edges for compare and obtain min-weight edge.
};

class EagerPrimMST
{
public:
    EagerPrimMST(EdgeWeightedGraph& g)
    {

    }

    ~EagerPrimMST()
    {

    }

    vector<Edge> Edges()
    {

    }

    double Weight()
    {

    }

private:
    void Visit(EdgeWeightedGraph& g, int v)
    {

    }

};

#endif
