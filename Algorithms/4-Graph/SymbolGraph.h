//**************************************************************
//                  Symbol Graph
//**************************************************************

#ifndef SYMBOLGRAPH_H
#define SYMBOLGRAPH_H

#include <fstream>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include "Graph.h"
#include "..\3-Search\SequentialSearchST.h"

using namespace std;

// symbol graph acts like a wrapper for Graph which allows string as vertex,
// by convert string to int and then use graph internally.
class SymbolGraph
{
public:
    // build graph specified in filename using delimiter to separate vertex names.
    SymbolGraph(string& filename, string& delimiter)
    {
        // read vertex string to construct st.
        ifstream inputFile(filename);
        string line;

        while (getline(inputFile, line))
        {
            // a line could contain multiple vertices.
            string vertex;
            vector<string> verticesOfLine;
            boost::split(verticesOfLine, line, boost::is_any_of(delimiter));

            for (auto name : verticesOfLine)
            {
                if (!st.Contains(name))
                {
                    Item item(name, st.Size());
                    st.Put(item);
                }
            }
        }

        // construct keys.
        keys = new string[st.Size()];
        std::vector<Key> keyContainer;
        st.Keys(keyContainer);

        for (auto name : keyContainer)
        {
            keys[st.Get(name).GetValue()] = name;
        }

        // construct graph by reading from file again.
        g = new Graph(st.Size());
        ifstream inputFileAgain(filename);
        while (getline(inputFileAgain, line))
        {
            string vertex;
            vector<string> verticesOfLine;
            boost::split(verticesOfLine, line, boost::is_any_of(delimiter));

            int firstVertex = st.Get(verticesOfLine[0]).GetValue();
            for (int i = 1; i < verticesOfLine.size(); i++)
            {
                g->AddEdge(firstVertex, st.Get(verticesOfLine[i]).GetValue());
            }
        }
    }

    ~SymbolGraph()
    {
        delete[] keys;
    }

    // is key a vertex?
    bool Contains(string& key)
    {
        return st.Contains(key);
    }

    // index associated with key
    int Index(string& key)
    {
        return st.Get(key).GetValue();
    }

    // key associated with index v
    string& Name(int v)
    {
        return keys[v];
    }

    // underlying graph
    Graph* graph()
    {
        return g;
    }

private:
    SequentialSearchST<string, Item> st; // string->index
    string* keys;                       // index->string
    Graph* g;
};

#endif
