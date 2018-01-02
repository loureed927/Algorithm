//**************************************************************
//                  Transitive Closure
//**************************************************************

#ifndef TRANSITIVECLOSURE_H
#define TRANSITIVECLOSURE_H

#include "Digraph.h"
#include "DirectedDFS.h"

class TransitiveClosure
{
//public:
//    TransitiveClosure(Digraph& g)
//    {
//        int vertices = g.Vertices();
//        num = vertices;
//        // this version creates array of DirectedDFS, need default contructor.
//        all = new DirectedDFS[vertices];
//        // computes and store transitive closure matrix of graph to support constant-times queries
//        // all pairs of vertices reachability.
//        for (int i = 0; i < vertices; i++)
//        {
//            // copy assignment op will be used here.
//            all[i] = DirectedDFS(g, i);
//        }
//    }
//
//    ~TransitiveClosure()
//    {
//        delete[] all;
//    }
//
//    // is w reachable from v?
//    bool Reachable(int v, int w)
//    {
//        return all[v].Marked(w);
//    }
//private:
//    DirectedDFS* all;
//    int num;

public:
    TransitiveClosure(Digraph& g)
    {
        // this version creates array of DirectedDFS*, no need for default constructor of DirectedDFS.
        int vertices = g.Vertices();
        num = vertices;
        all = new DirectedDFS*[vertices];
        // computes and store transitive closure matrix of graph to support constant-times queries
        // all pairs of vertices reachability.
        for (int i = 0; i < vertices; i++)
        {
            // so here element of array is pointer points to a new created DirectedDFS,
            // not copy assignment of DirectedDFS will not be called.
            all[i] = new DirectedDFS(g, i);
        }
    }

    ~TransitiveClosure()
    {
        delete[] all;
    }

    // is w reachable from v?
    bool Reachable(int v, int w)
    {
        return all[v]->Marked(w);
    }
private:
    DirectedDFS** all;
    int num;
};
#endif
