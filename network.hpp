#ifndef _NETWORK
#define _NETWORK

#include <vector>
#include "double-edge.hpp"
#include "graph.hpp"

class Network: public Graph {
    ui32 numberVertices, numberEdges;
    ui32 source, sink;
    void addEdge(ui32 edgeBegin, ui32 edgeEnd, ui32 edgeCapacity);
    vector<vector<DoubleEdge*>> edges;
    vector<DoubleEdge*> edgesById;
public:
    void read(istream &in);
    DoubleEdge* getEdge(ui32 vertex, ui32 edgeID);
    ui32 getDegree(ui32 vertex);
    vector<ui32> blockingBFS(ui32 vertex);
    void printFlowById(ostream& out);
    void printAnswer(ostream& out);
    ui32 getSource();
    ui32 getSink();
    ui32 getNumberVertices();
    friend istream& operator >> (istream& in, Network& network);
    friend ostream& operator << (ostream& out, Network& network);
};
#endif
