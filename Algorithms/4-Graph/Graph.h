//**************************************************************
//                  Graph
//**************************************************************

#ifndef GRAPH_H
#define GRAPH_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

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
        adjacencyLists = new vector<int>[v];
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
        int edgeNum = 0;
        getline(file, line);
        istringstream secondLine(line);
        secondLine >> edgeNum;

        // read e pairs of edges.
        for (int i = 0; i < edgeNum; i++)
        {
            getline(file, line);
            istringstream LineForEdges(line);
            int v1 = 0;
            int v2 = 0;
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
        adjacencyLists[v].push_back(w);
        adjacencyLists[w].push_back(v);
        e++;
    }

    // vertices adjacent to v.
    vector<int>& AdjacentToVertex(int v)
    {
        return adjacencyLists[v];
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
            for (int adj : adjacencyLists[i])
            {
                ss << adj << " ";
            }
            ss << "\n";
        }

        return ss.str();
    }

private:
    int v; // number of vertices.
    int e; // number of edges.
    vector<int>* adjacencyLists; // a vertex-indexed array, size of v, each list contains vertices adjacent to this vertex.
};

#endif

