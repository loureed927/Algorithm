//**************************************************************
//                  Edge Weighted Directed Graph
//**************************************************************

#ifndef EDGEWEIGHTEDIDGRAPH_H
#define EDGEWEIGHTEDIDGRAPH_H

#include <fstream>
#include <sstream>
#include <string>
#include <forward_list>
#include "DirectedEdge.h"

using namespace std;

// edge weighted digraph. similar to EdgeWeightDigraph implementation.
class EdgeWeightedDigraph
{
public:
    // create a V-vertex graph.
    EdgeWeightedDigraph(int v)
    {
        this->v = v;
        this->e = 0;
        // each vertex has an adjacencylist contains all edges points from it.
        adjacencyLists = new forward_list<DirectedEdge>[v];
    }

    // read a graph from input stream.
    // the input stream follows format: 
    // number of v,
    // number of e,
    // e pairs of edges: integer values(0, v-1) and its weight.
    EdgeWeightedDigraph(std::ifstream& file)
    {
        // read v and construct graph.
        string line;
        getline(file, line);
        istringstream firstline(line);
        firstline >> v;

        // using replacement new here.
        new (this)EdgeWeightedDigraph(v);

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

            AddEdge(DirectedEdge(v, w, weight));
        }
    }

    ~EdgeWeightedDigraph()
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

    // add directed edge to this graph.
    void AddEdge(DirectedEdge& edge)
    {
        int v = edge.From();
        int w = edge.To();
        adjacencyLists[v].push_front(edge);
        e++;
    }

    // edges points from v.
    forward_list<DirectedEdge>& AdjacentToVertex(int v)
    {
        return adjacencyLists[v];
    }

    // all directed edges of this graph.
    vector<DirectedEdge> AllEdges()
    {
        vector<DirectedEdge> allEdges;
        for (int i = 0; i < Vertices(); i++)
        {
            for (DirectedEdge& e : AdjacentToVertex(i))
            {
                allEdges.push_back(e);
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
            for (DirectedEdge& adj : adjacencyLists[i])
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

    // a vertex-indexed array, size of v, each list contains edges points from this vertex.
    // note use forward_list here to push item afront, keep consistent with Bag used by book.
    forward_list<DirectedEdge>* adjacencyLists;
};

#endif

