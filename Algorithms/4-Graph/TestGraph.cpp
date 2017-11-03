//**************************************************************
//          main test routine for graph algorithms
//**************************************************************

#include <fstream>
#include <iostream>
#include "Graph.h"

using namespace std;

void GraphConstruct_TestClient()
{
    ifstream inputFile("tinyG.txt");
    Graph g(inputFile);
    cout << g.ToString() << endl;
}

int main()
{
    GraphConstruct_TestClient();
}

