//**************************************************************
//                  Edge Weighted Undirected Graph
//**************************************************************

#ifndef EDGEWEIGHTEDGRAPH_H
#define EDGEWEIGHTEDGRAPH_H

#include <fstream>
#include <sstream>
#include <string>
#include <forward_list>
#include "Edge.h"

using namespace std;

// edge weighted graph.
class EdgeWeightedGraph
{
public:
    // create a V-vertex graph.
    EdgeWeightedGraph(int v)
    {
        this->v = v;
        this->e = 0;
        // each vertex has an adjacencylist contains all edges connected to it.
        adjacencyLists = new forward_list<Edge>[v];
    }

    // read a graph from input stream.
    // the input stream follows format: 
    // number of v,
    // number of e,
    // e pairs of edges: integer values(0, v-1) and its weight.
    EdgeWeightedGraph(std::ifstream& file)
    {
        // read v and construct graph.
        string line;
        getline(file, line);
        istringstream firstline(line);
        firstline >> v;

        // using replacement new here.
        new (this)EdgeWeightedGraph(v);

        // read e.
        int edgeNum = 0;
        getline(file, line);
        istringstream secondLine(line);
        secondLine >> edgeNum;

        // read e pairs of edges.
        for (int i = 0; i < edgeNum; i++)
        {
            getline(file, line);
            istringstream LineForEdges(line);
            int v = 0;
            int w = 0;
            double weight = 0.0;
            LineForEdges >> v;
            LineForEdges >> w;
            LineForEdges >> weight;

            AddEdge(Edge(v, w, weight));
        }
    }

    ~EdgeWeightedGraph()
    {
        delete[] adjacencyLists;
    }

    // number of vertices.
    int Vertices()
    {
        return v;
    }

    // number of edges.
    int Edges()
    {
        return e;
    }

    // add edge to this graph.
    void AddEdge(Edge& edge)
    {
        int v = edge.Either();
        int w = edge.Other(v);
        adjacencyLists[v].push_front(edge);
        adjacencyLists[w].push_front(edge);
        e++;
    }

    // edges adjacent to v.
    forward_list<Edge>& AdjacentToVertex(int v)
    {
        return adjacencyLists[v];
    }

    // all edges of this graph.
    vector<Edge> AllEdges()
    {
        vector<Edge> allEdges;
        for (int i = 0; i < Vertices(); i++)
        {
            for (Edge& e : AdjacentToVertex(i))
            {
                // to exclude duplicate edge.
                if (e.Other(i) > i)
                {
                    allEdges.push_back(e);
                }
            }
        }
        return allEdges;
    }

    // note should not return string& which reference a local variable.
    string ToString()
    {
        // compose a stringstream contains graph information.
        stringstream ss;
        ss << Vertices() << " vertices. " << Edges() << " adges.\n";
        for (int i = 0; i < Vertices(); i++)
        {
            ss << i << ": ";
            for (Edge& adj : adjacencyLists[i])
            {
                ss << adj.ToString() << " ";
            }
            ss << "\n";
        }

        return ss.str();
    }

private:
    int v; // number of vertices.
    int e; // number of edges.

    // a vertex-indexed array, size of v, each list contains edges adjacent to this vertex.
    // note use forward_list here to push item afront, keep consistent with Bag used by book.
    forward_list<Edge>* adjacencyLists;
};

#endif

