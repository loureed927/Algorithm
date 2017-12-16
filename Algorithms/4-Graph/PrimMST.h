//**************************************************************
//         Prim's Algorithm For Minimum Spanning Trees(MST)
//**************************************************************

#ifndef PRIMMST_H
#define PRIMMST_H

#include <vector>
#include "Edge.h"
#include "EdgeWeightedGraph.h"
#include "..\2-Sort\PriorityQueue.h"

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
            mst.push_back(e);
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
    vector<Edge> Edges()
    {
        return mst;
    }

    // weight of MST.
    double Weight()
    {
        double weight = 0.0;
        // since queue cannot iterator, copy element to a vector.
        for (Edge& e : mst)
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

        for (Edge& e : g.AdjacentToVertex(v))
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
    vector<Edge> mst; // MST edges. use vector instead of queue from textbook since std queue connot iterator.
    priority_queue<Edge, vector<Edge>, greater<Edge>> pq; // crossing (and ineligible) edges for compare and obtain min-weight edge.
};

class EagerPrimMST
{
public:
    EagerPrimMST(EdgeWeightedGraph& g)
    {
        int vertices = g.Vertices();
        numVectices = vertices;
        marked = new bool[vertices];
        edgeTo = new Edge[vertices];
        distTo = new double[vertices];
        for (int m = 0; m < vertices; m++)
        {
            marked[m] = false;
            // define initial value for distTo as positive infinity, so Visit can always add edge first time.
            distTo[m] = std::numeric_limits<double>::max();
        }

        pq = new IndexMinPQ<double>(vertices);

        // start from vertex 0.
        Visit(g, 0);

        while (!pq->IsEmpty())
        {
            // get vertex in mst, and remove it from pq.
            int VertexToBeAdded = pq->DeleteMin();

            Visit(g, VertexToBeAdded);
        }
    }

    ~EagerPrimMST()
    {
        delete[] marked;
        delete[] edgeTo;
        delete[] distTo;
        delete pq;
    }

    vector<Edge> Edges()
    {
        vector<Edge> mst;
        for (int i = 1; i < numVectices; i++)
        {
            mst.push_back(edgeTo[i]);
        }
        return mst;
    }

    double Weight()
    {
        double weight = 0.0;
        for (int i = 1; i < numVectices; i++)
        {
            weight += distTo[i];
        }
        return weight;
    }

private:
    void Visit(EdgeWeightedGraph& g, int v)
    {
        marked[v] = true;

        for (auto e : g.AdjacentToVertex(v))
        {
            int w = e.Other(v);
            // if adjacent vertex is already in the MST which is marked, then the edge is ineligible.
            if (!marked[e.Other(v)])
            {
                // if e(v-w) is not in the pq or its weight is less than edgeTo[w],
                // then insert this edge to priority queue.
                // this minPQ's first item is the crossing edge which has minimum weight.
                if (e.Weight() < distTo[w])
                {
                    edgeTo[w] = e;
                    distTo[w] = e.Weight();

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
    }

    bool* marked; // true if v on the tree.
    Edge* edgeTo; // shortest edge from tree vertex.
    double* distTo; // weight of edgeTo;
    IndexMinPQ<double>* pq; // eligible crossing edge. the minimum one is the edge connecting candidate
                           // vertex to the tree.
    int numVectices;
};

#endif
