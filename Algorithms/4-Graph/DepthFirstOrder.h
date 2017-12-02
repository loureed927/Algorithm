//**************************************************************
//                  Depth First Order
//**************************************************************

#ifndef DEPTHFIRSTORDER_H
#define DEPTHFIRSTORDER_H

#include <queue>
#include <stack>
#include "Digraph.h"

using namespace std;

// save vertex of dfs which is argument of dfs method in some data structure.
// iterate data structure to get the dfs order.
class DepthFirstOrder
{
public:
    DepthFirstOrder(Digraph& g)
    {
        int vertices = g.Vertices();
        marked = new bool[vertices];
        for (int m = 0; m < vertices; m++)
        {
            marked[m] = false;
        }

        for (int m = 0; m < vertices; m++)
        {
            if (!marked[m])
            {
                dfs(g, m);
            }
        }
    }

    ~DepthFirstOrder()
    {
        delete[] marked;
    }

    // to return all typical orders.
    queue<int> PreOrder()
    {
        return pre;
    }

    queue<int> PostOrder()
    {
        return post;
    }

    stack<int> ReversePostOrder()
    {
        return reversePost;
    }

private:
    void dfs(Digraph& g, int v)
    {
        // to visit a vertex, marked it as having been visited.
        marked[v] = true;

        // cache vertex in preorder by adding current vertex to queue before recursive calls.
        pre.push(v);

        for (int a : g.AdjacentToVertex(v))
        {
            // if adjacent vertex of v is not visited, continue with dfs.
            if (!marked[a])
            {
                dfs(g, a);
            }
        }

        // cache vertex in postorder after recursive calls.
        post.push(v);
        reversePost.push(v);
    }

    bool* marked; // array of bool values to mark all of the vertices that are connected to the source or not.

    queue<int> pre; // vertices in preorder.
    queue<int> post; // vertices in postorder.
    stack<int> reversePost; // vertices in reverse postorder.
};

#endif
