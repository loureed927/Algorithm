//**************************************************************
//                  Edge
//**************************************************************

#ifndef EDGE_H
#define EDGE_H

#include <string>
#include <boost/format.hpp>

using namespace std;

// weighted edge
class Edge
{
public:
    Edge() = default;

    Edge(int v, int w, double weight)
    {
        this->v = v;
        this->w = w;
        this->weight = weight;
    }

    ~Edge()
    {
    }

    bool operator< (const Edge& e) const
    {
        return this->weight < e.weight;
    }

    bool operator> (const Edge& e) const
    {
        return this->weight > e.weight;
    }

    bool operator== (const Edge& e) const
    {
        return this->weight == e.weight;
    }

    bool operator!= (const Edge& e) const
    {
        return this->weight != e.weight;
    }

    double Weight()
    {
        return weight;
    }

    // either of this edge's vertices.
    int Either()
    {
        return v;
    }

    // the other vertex.
    int Other(int vertex)
    {
        if (vertex == v)
        {
            return w;
        }
        else if (vertex == w)
        {
            return v;
        }
        else
        {
            throw(vertex);
        }
    }

    string ToString()
    {
        return str(boost::format("%d - %d %.2f") % v %w %weight);
    }

private:
    int v;
    int w;
    double weight;
};

#endif
