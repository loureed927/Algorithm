//**************************************************************
//                  Directed Graph
//**************************************************************

#ifndef DIGRAPH_H
#define DIGRAPH_H

#include <fstream>
#include <sstream>
#include <string>
#include <forward_list>

using namespace std;

// directed graph
class Digraph
{
public:
    // create a V-vertex graph with no edges.
    Digraph(int v)
    {
        this->v = v;
        this->e = 0;
        adjacencyLists = new forward_list<int>[v];
    }

    // read a graph from input stream.
    // the input stream follows format: 
    // number of v,
    // number of e,
    // e pairs of integer values(0, v-1), each pair denotes an edge.
    Digraph(std::ifstream& file)
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

    // since Digraph contain pointer member data, need copy construct here.
    // in Reverse method, local graph object will be deconstruct and copy construct
    // needs to be called to deep copy graph object. otherwise adjacentList of copied
    // object will be empty.
    Digraph(Digraph& g)
    {
        this->v = g.Vertices();
        this->e = g.Edges();
        this->adjacencyLists = new forward_list<int>[v];
        for (int i = 0; i < v; i++)
        {
            adjacencyLists[i] = g.AdjacentToVertex(i);
        }
    }

    // deep copy also for copy-assignment operator.
    Digraph& operator=(Digraph& g)
    {
        this->v = g.Vertices();
        this->e = g.Edges();
        this->adjacencyLists = new forward_list<int>[v];
        for (int i = 0; i < v; i++)
        {
            adjacencyLists[i] = g.AdjacentToVertex(i);
        }
        return *this;
    }

    ~Digraph()
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

    // add edge v->w to this digraph.
    void AddEdge(int v, int w)
    {
        // add an edge connecting v and w by:
        // add w to v's adjacency list. Note this is different from undirected graph.
        adjacencyLists[v].push_front(w);
        e++;
    }

    // vertices connected to v by edges pointing from v.
    forward_list<int>& AdjacentToVertex(int v)
    {
        return adjacencyLists[v];
    }

    // reverse of this digraph.
    // useful when needs to find the edges that point to each vertex,
    // while AdjacentToVertex can only give vertices connected by edges
    // that point from each vertex.
    Digraph Reverse()
    {
        Digraph dg(v);
        for (int i = 0; i < v; i++)
        {
            for (auto a : this->AdjacentToVertex(i))
            {
                // add reversed edges.
                dg.AddEdge(a, i);
            }
        }
        return dg;
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

    // a vertex-indexed array, size of v, each list contains vertices adjacent to this vertex.
    // note use forward_list here to push item afront, keep consistent with Bag used by book.
    forward_list<int>* adjacencyLists;
};

#endif
