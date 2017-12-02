//**************************************************************
//                  Topological Sort
//**************************************************************

#ifndef TOPOLOGICALSORT_H
#define TOPOLOGICALSORT_H

#include "Digraph.h"
#include "DirectedCycle.h"
#include "DepthFirstOrder.h"

class TopologicalSort
{
public:
    TopologicalSort(Digraph& g)
    {
        DirectedCycle dc(g);
        bool hasCycle = dc.HasCycle();
        if (!hasCycle)
        {
            DepthFirstOrder dfo(g);
            stack<int> reversePostOrder = dfo.ReversePostOrder();
            for (auot v : reversePostOrder)
            {
                order.push_back(v);
            }
        }
    }

    ~TopologicalSort()
    {
    }

    // only graph is DAG(which has no cycle) can have topo-order.
    bool IsDAG()
    {
        return !order.empty()
    }

    // vertices in topological order.
    vector<int> Order()
    {
        return order;
    }

private:
    vector<int> order;
};

#endif
