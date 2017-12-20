//**************************************************************
//          main test routine for graph algorithms
//**************************************************************

#include <fstream>
#include <iostream>
// undirected graph.
#include "Graph.h"
#include "DepthFirstSearch.h"
#include "DepthFirstPaths.h"
#include "BreadthFirstPaths.h"
#include "ConnectedComponents.h"
#include "CycleDetection.h"
#include "BipartiteDetection.h"
#include "SymbolGraph.h"
#include "DegreesOfSeparation.h"
// digraph.
#include "Digraph.h"
#include "DirectedDFS.h"
#include "DirectedCycle.h"
#include "DepthFirstOrder.h"
#include "KosarajuSCC.h"
#include "TransitiveClosure.h"
// mst.
#include "EdgeWeightedGraph.h"
#include "PrimMST.h"
// shortest paths.
#include "EdgeWeightedDigraph.h"
#include "DijkstraSP.h"


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

    cout << "All vertices connected to source vertex " << source << ":" << endl;

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
    cout << "The graph is ";
    if (dfs.Count() != g.Vertices())
    {
        cout << "NOT";
    }
    cout << " connected.\n" << endl;
}

void GraphDFSPaths_TestClient(int source)
{
    ifstream inputFile("tinyCG.txt");
    Graph g(inputFile);
    DepthFirstPaths paths(g, source);

    cout << "DFS Paths from source " << source << " to each vertex connected to source:" << endl;

    // loop all vertices, print paths connected to source.
    for (int v = 0; v < g.Vertices(); v++)
    {
        cout << source << " to " << v << ": ";
        if (paths.HasPathTo(v))
        {
            std::stack<int> pathStack(paths.PathTo(v));

            // get path vertex from start by pop the stack.
            while (!pathStack.empty())
            {
                int pathNode = pathStack.top();

                if (pathNode == source)
                {
                    cout << pathNode;
                }
                else
                {
                    cout << "-" << pathNode;
                }

                pathStack.pop();
            }
            cout << endl;
        }
    }
}

void GraphBFSPaths_TestClient(int source)
{
    ifstream inputFile("tinyCG.txt");
    Graph g(inputFile);
    BreadthFirstPaths paths(g, source);

    cout << "BFS Paths from source " << source << " to each vertex connected to source:" << endl;

    // loop all vertices, print paths connected to source.
    for (int v = 0; v < g.Vertices(); v++)
    {
        cout << source << " to " << v << ": ";
        if (paths.HasPathTo(v))
        {
            std::stack<int> pathStack(paths.PathTo(v));

            // get path vertex from start by pop the stack.
            while (!pathStack.empty())
            {
                int pathNode = pathStack.top();

                if (pathNode == source)
                {
                    cout << pathNode;
                }
                else
                {
                    cout << "-" << pathNode;
                }

                pathStack.pop();
            }
            cout << endl;
        }
    }
}

void GraphCC_TestClient()
{
    ifstream inputFile("tinyG.txt");
    Graph g(inputFile);
    ConnectedComponents cc(g);

    int n = cc.Count();
    cout << n << " components" << endl;

    vector<int>* components = new vector<int>[n];
    for (int i = 0; i < g.Vertices(); i++)
    {
        // add each vertex to component vector.
        int index = cc.Id(i);
        components[index].push_back(i);
    }

    // print elements of each components.
    for (int j = 0; j < n; j++)
    {
        for (int v : components[j])
        {
            cout << v << " ";
        }
        cout << endl;
    }

    delete[] components;
}

void GraphCyclic_TestClient()
{
    ifstream inputFile("tinyG.txt");
    Graph g(inputFile);
    CycleDetection cd(g);

    bool isCyclicGraph = cd.HasCycle();

    cout << "The graph is ";
    if (isCyclicGraph)
    {
        cout << "cyclic.\n" << endl;
    }
    else
    {
        cout << "acyclic.\n" << endl;
    }
}

void GraphBipartite_TestClient()
{
    ifstream inputFile("tinyG.txt");
    Graph g(inputFile);
    BipartiteDetection bd(g);

    bool isBipartite = bd.IsBipartite();

    cout << "The graph is ";
    if (!isBipartite)
    {
        cout << "NOT";
    }

    cout << " bipartite." << endl;
}

void SymbolGraph_TestClient()
{
    SymbolGraph sg(string("routes.txt"), string(" "));
    //SymbolGraph sg(string("movies.txt"), string("/"));
    Graph* g = sg.GetGraph();

    string name;
    cout << "input vertex name:";

    // use getline not cin>>name to get whole stirng including white space...
    while (getline(cin, name))
    {
        if (sg.Contains(name))
        {
            cout << "All adjacent vertex names:" << endl;
            for (auto a : g->AdjacentToVertex(sg.Index(name)))
            {
                cout << sg.Name(a) <<endl;
            }
            cout << endl;

            cout << "input vertex name:";
        }
        else if (strcmp(name.c_str(), "Q") == 0)
        {
            // press Q to exit input.
            break;
        }
        else
        {
            cout << "Cannot find any input string in symbol graph." << endl;
            cout << "Please input vertex name again:";
        }
    }
}

void DegreesOfSeparation_TestClient()
{
    DegreesOfSeparation::CalculateDOS(string("routes.txt"), string(" "), string("JFK"));
}

void DigraphDFS_TestClient()
{
    ifstream inputFile("tinyDG.txt");
    Digraph g(inputFile);

    cout << "Please input sources to query all reachable vertices:";

    string source;
    vector<int> sources;
    // get input vertices from standard input by one line.
    getline(cin, source);
    stringstream ss;
    ss << source;
    int sourceIndx = 0;
    // convert string input to int by stringstream.
    while (!ss.eof())
    {
        ss >> sourceIndx;
        sources.push_back(sourceIndx);
    }

    DirectedDFS dfs(g, sources);

    cout << "All reachable vertices to sources: " << endl;

    // loop all vertices, print vertices connected to source.
    for (int v = 0; v < g.Vertices(); v++)
    {
        if (dfs.Marked(v))
        {
            cout << v << " ";
        }
    }
    cout << endl;
}

void DirectedCycle_TestClient()
{
    //ifstream inputFile("tinyDG.txt");
    ifstream inputFile("tinyDAG.txt");
    Digraph g(inputFile);
    DirectedCycle dc(g);

    bool isDAG = !dc.HasCycle();

    cout << "The graph is ";
    if (!isDAG)
    {
        cout << "not DAG.\n" << endl;
        cout << "All vertices in a cycle:";
        stack<int> cycle = dc.Cycle();
        while (!cycle.empty())
        {
            int vertex = cycle.top();
            cout << " " << vertex;
            cycle.pop();
        }
        cout << endl;
    }
    else
    {
        cout << "DAG.\n" << endl;
    }
}

void SCC_TestClient()
{
    ifstream inputFile("tinyDG.txt");
    Digraph g(inputFile);
    KosarajuSCC scc(g);

    int n = scc.Count();
    cout << n << " components" << endl;

    vector<int>* components = new vector<int>[n];
    for (int i = 0; i < g.Vertices(); i++)
    {
        // add each vertex to component vector.
        int index = scc.Id(i);
        components[index].push_back(i);
    }

    // print elements of each components.
    for (int j = 0; j < n; j++)
    {
        for (int v : components[j])
        {
            cout << v << " ";
        }
        cout << endl;
    }

    delete[] components;
}

void TransitiveClosure_TestClient()
{
    ifstream inputFile("tinyDG.txt");
    Digraph g(inputFile);
    TransitiveClosure tc(g);

    int v = 0;
    int w = 2;
    //int v = 1;
    //int w = 8;
    bool isReachable = tc.Reachable(v, w);
    cout << w << " is";
    if (isReachable)
    {
        cout << " reachable from " << v << endl;
    }
    else
    {
        cout << " not reachable from " << v << endl;
    }
}

void MST_TestClient()
{
    ifstream inputFile("tinyEWG.txt");
    EdgeWeightedGraph g(inputFile);
    //LazyPrimMST mst(g);
    EagerPrimMST mst(g);

    cout << "Edges in MST:" << endl;
    for (auto e : mst.Edges())
    {
        cout << e.ToString() << endl;
    }
    cout << "Weight of MST: ";
    cout << mst.Weight() << endl;
}

void SPT_TestClient()
{
    ifstream inputFile("tinyEWD.txt");
    //ifstream inputFile("tinyspt.txt"); // simple test case to run relaxation
    EdgeWeightedDigraph g(inputFile);
    int s = 0;
    DijkstraSP spt(g, s);

    // output paths and weight from source to all vertices.
    for (int i = 0; i < g.Vertices(); i++)
    {
        string dist = str(boost::format("%4.2f") %spt.DistTo(i));
        cout << s << " to " << i << " (" << dist << "): ";

        if (spt.HasPathTo(i))
        {
            stack<DirectedEdge> pathStack(spt.PathTo(i));

            while (!pathStack.empty())
            {
                auto edge = pathStack.top();

                cout << edge.ToString() << "  ";

                pathStack.pop();
            }
            cout << endl;
        }
    }
}

int main()
{
    // undirected graph.
    //GraphConstruct_TestClient();
    //GraphDFS_TestClient(0);
    //GraphDFS_TestClient(9);
    //GraphDFSPaths_TestClient(0);
    //GraphBFSPaths_TestClient(0);
    //GraphCC_TestClient();
    //GraphCyclic_TestClient();
    //GraphBipartite_TestClient();
    //SymbolGraph_TestClient();
    //DegreesOfSeparation_TestClient();

    // directed graph.
    //DigraphDFS_TestClient();
    //DirectedCycle_TestClient();
    //SCC_TestClient();
    //TransitiveClosure_TestClient();

    // mst.
    //MST_TestClient();

    // spt.
    SPT_TestClient();
}
