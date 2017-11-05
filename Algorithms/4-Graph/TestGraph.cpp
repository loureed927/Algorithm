//**************************************************************
//          main test routine for graph algorithms
//**************************************************************

#include <fstream>
#include <iostream>
#include "Graph.h"
#include "DepthFirstSearch.h"

using namespace std;

void GraphConstruct_TestClient()
{
    ifstream inputFile("tinyG.txt");
    Graph g(inputFile);
    cout << g.ToString() << endl;
}

void GraphDFS_TestClient(int source)
{
    ifstream inputFile("tinyG.txt");
    Graph g(inputFile);
    DepthFirstSearch dfs(g, source);

    // loop all vertices, print vertices connected to source.
    for (int v = 0; v < g.Vertices(); v++)
    {
        if (dfs.Marked(v))
        {
            cout << v << " " << endl;
        }
    }

    // print whether the graph is connected.
    // the graph is connected if and only if the search marked all of its vertices.
    if (dfs.Count() != g.Vertices())
    {
        cout << "NOT";
    }
    cout << "connected" << endl;
}

int main()
{
    GraphConstruct_TestClient();
    GraphDFS_TestClient(0);
    GraphDFS_TestClient(9);
}

