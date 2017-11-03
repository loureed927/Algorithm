//**************************************************************
//                  Graph
//**************************************************************

#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include <sstream>
#include <string>
#include "..\1-Fundamentals\Bag.h"

using namespace std;

// undirected graph
class Graph
{
public:
    // create a V-vertex graph with no edges.
    Graph(int v)
    {
        this->v = v;
        this->e = 0;
        adjacencyLists = new LinkedListBag<int>[v];
    }

    // read a graph from input stream.
    // the input stream follows format: 
    // number of v,
    // number of e,
    // e pairs of integer values(0, v-1), each pair denotes an edge.
    Graph(std::ifstream& file)
    {
        // read v and construct graph.
        string line;
        getline(file, line);
        istringstream firstline(line);
        firstline >> v;

        // using replacement new here.
        new (this)Graph(v);

        // read e.
        getline(file, line);
        istringstream secondLine(line);
        secondLine >> e;

        // read e pairs of edges.
        for (int i = 0; i < e; i++)
        {
            getline(file, line);
            istringstream LineForEdges(line);
            int v1, v2 = 0;
            LineForEdges >> v1;
            LineForEdges >> v2;
            AddEdge(v1, v2);
        }
    }

    ~Graph()
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

    // add edge v-w to this graph.
    void AddEdge(int v, int w)
    {
        // add an edge connecting v and w by:
        // add w to v's adjacency list and then add v to w's.
        adjacencyLists[v].add(w);
        adjacencyLists[w].add(v);
        e++;
    }

    // vertices adjacent to v.
    LinkedListBag<int>& AdjacentToVertex(int v)
    {
        return adjacencyLists[v];
    }

private:
    int v; // number of vertices.
    int e; // number of edges.
    LinkedListBag<int>* adjacencyLists; // a vertex-indexed array, size of v, each list contains vertices adjacent to this vertex.
};

#endif

