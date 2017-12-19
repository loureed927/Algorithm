//**************************************************************
//                  Directed Edge for Digraph
//**************************************************************

#ifndef DIRECTEDEDGE_H
#define DIRECTEDEDGE_H

#include <string>
#include <boost/format.hpp>

using namespace std;

// weighted directed edge
class DirectedEdge
{
public:
    DirectedEdge() = default;

    DirectedEdge(int v, int w, double weight)
    {
        this->v = v;
        this->w = w;
        this->weight = weight;
    }

    ~DirectedEdge()
    {
    }

    bool operator< (const DirectedEdge& e) const
    {
        return this->weight < e.weight;
    }

    bool operator>(const DirectedEdge& e) const
    {
        return this->weight > e.weight;
    }

    bool operator== (const DirectedEdge& e) const
    {
        return this->weight == e.weight;
    }

    bool operator!= (const DirectedEdge& e) const
    {
        return this->weight != e.weight;
    }

    double Weight()
    {
        return weight;
    }

    // vertex that this edge points from.
    int From()
    {
        return v;
    }

    // vertex that this edge points from.
    int To()
    {
        return w;
    }

    // if edge is self-cycle (v->v), define it as null edge.
    bool IsNull()
    {
        return v == w;
    }

    string ToString()
    {
        return str(boost::format("%d -> %d %.2f") % v %w %weight);
    }

private:
    int v; // edge source.
    int w; // edge target.
    double weight; // edge weight.
};

#endif
