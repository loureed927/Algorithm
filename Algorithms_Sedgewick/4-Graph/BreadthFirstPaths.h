//**************************************************************
//                  Breadth First Paths
//**************************************************************

#ifndef BREADTHFIRSTPATHS_H
#define BREADTHFIRSTPATHS_H

#include <queue>
#include <stack>
#include "Graph.h"

// to find single source shortest paths.
class BreadthFirstPaths
{
public:
    BreadthFirstPaths(Graph& g, int s)
    {
        int vertices = g.Vertices();
        marked = new bool[vertices];
        edgeTo = new int[vertices];
        this->s = s;

        for (int m = 0; m < vertices; m++)
        {
            marked[m] = false;
            edgeTo[m] = s;
        }

        bfs(g, s);
    }

    ~BreadthFirstPaths()
    {
        delete[] marked;
        delete[] edgeTo;
    }

    // same as Marked from DepthFirstSearch to indicate v is connected to s or not.
    bool HasPathTo(int v)
    {
        return marked[v];
    }

    // same as DepthFirstPath. and paths has the property that no other such path from s to v has fewer edges.
    std::stack<int> PathTo(int v)
    {
        std::stack<int> path;
        if (!HasPathTo(v))
            return path;

        for (int x = v; x != s; x = edgeTo[x])
        {
            path.push(x);
        }
        path.push(s);

        return path;
    }

private:
    void bfs(Graph& g, int v)
    {
        // to visit a vertex, marked it as having been visited.
        marked[v] = true;

        std::queue<int> toBeMarked;
        toBeMarked.push(v);

        while (!toBeMarked.empty())
        {
            int thisLevel = toBeMarked.front();
            // push all unmarked vertices next level to queue.
            for (int nextLevel : g.AdjacentToVertex(thisLevel))
            {
                if (!marked[nextLevel])
                {
                    toBeMarked.push(nextLevel);

                    marked[nextLevel] = true;
                    edgeTo[nextLevel] = thisLevel;
                }
            }

            // pop vertex this level. If there are other vertex in the queue, continue.
            // for tinyG.txt: thisLevel begins with 0, queue is with 0.
            // nextLevel are 2,1,5, all unmarked so push them to queue.
            // now queue is 0, 2, 1, 5. then pop the 0.
            // front now is 2, nextLevel are 0,1,3,4. so push 3, 4 in the queue.
            // Now queue is 2, 1, 5, 3, 4, done with 2, we pop 2, then continue with 1...
            toBeMarked.pop();
        }
    }

    bool* marked; // array of bool values to mark all of the vertices that are connected to the source.
    int* edgeTo; // last vertex on known path to this vertex.
    int s; // source
};

#endif
