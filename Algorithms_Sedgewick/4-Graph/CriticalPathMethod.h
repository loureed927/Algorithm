//**************************************************************
//                  Critical Path Method
//**************************************************************

#ifndef CRITICALPATHMETHOD_H
#define CRITICALPATHMETHOD_H

#include <iostream>
#include <string>
#include <boost/tokenizer.hpp> // use tokenizer not string split here since delimiter maybe string(multiple white spaces).

#include "DirectedEdge.h"
#include "EdgeWeightedDigraph.h"
#include "AcyclicLP.h"

using namespace std;
using namespace boost;

// Parallel precedence-constrained job scheduling problem : 
// Given a set of jobs of specified duration to be completed, with precedence constraints that specify
// that certain jobs have to be completed before certain other jobs are begun, how can we schedule the
// jobs on identical processors(as many as needed) such that they are all completed in the minimum 
// amount of time while still respecting the constraints?

// The critical path method (CPM) for parallel precedence-constrained scheduling is equivalent to
// longest-paths problem in edge-weighted DAG.

class CriticalPathMethod
{
public:
    static void CalculateSchechule(ifstream& file)
    {
        // Create edge-weighted DAG with a source s, a sink t, and two vertices for each job (a start vertex and an end vertex).
        // For each job, add an edge from its start vertex to its end vertex with wight equal to its duration.
        // also add zero-weighted edge from source to start vertex and from end vertex to sink.
        // For each precedence constraint v->w, add a zero-weighted from v's end vertex to w's start vertex.
        // so the graph has three edges for each job and one edge for each constraint, the number of vertex will be 2*n+2.

        // first line is num of jobs.
        int n = 0;
        string line;
        getline(file, line);
        istringstream firstline(line);
        firstline >> n;

        EdgeWeightedDigraph g(2 * n + 2);

        // vertex for source and sink.
        int source = 2 * n;
        int sink = 2 * n + 1;

        // read weight/constraint for each job.
        for (int i = 0; i < n; i++)
        {
            getline(file, line);

            typedef tokenizer<char_separator<char>> tokenizer;
            char_separator<char> sep(" ", 0, drop_empty_tokens); // drop any white space of input line.
            tokenizer tok(line, sep);

            tokenizer::iterator head = tok.begin();
            istringstream weightStr(*head);
            double weight = 0.0;
            weightStr >> weight;
            head++;

            // add edge for vertex i.
            g.AddEdge(DirectedEdge(i, i + n, weight));
            g.AddEdge(DirectedEdge(source, i, 0.0));
            g.AddEdge(DirectedEdge(i + n, sink, 0.0));

            // from second element, all is vertices.
            for (tokenizer::iterator beg = head; beg != tok.end(); ++beg)
            {
                istringstream vertexStr(*beg);
                int v = 0;
                vertexStr >> v;
                // add edge for constraint.
                g.AddEdge(DirectedEdge(i + n, v, 0.0));
            }
        }

        AcyclicLP lp(g, source);

        cout << "Start times:" << endl;
        for (int i = 0; i < n; i++)
        {
            cout << str(boost::format("%4d: %5.1f\n") %i %lp.DistTo(i));
        }
        cout << str(boost::format("Finish time: %5.1f\n") %lp.DistTo(sink));
    }

private:
    CriticalPathMethod() = delete;
    ~CriticalPathMethod() = delete;
    CriticalPathMethod(const CriticalPathMethod&) = delete;
    CriticalPathMethod& operator=(const CriticalPathMethod&) = delete;
};

#endif
