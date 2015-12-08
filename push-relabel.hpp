#ifndef _PUSH_RELABEL
#define _PUSH_RELABEL

#include <vector>
#include "max-flow-solver.hpp"
#include "graph.hpp"
#include "double-edge.hpp"
#include "network.hpp"

class PushRelabel: public MaxFlowSolver {
    ui32 numberVertices;
    vector<ui32>currentEdge, height, sizeHeight;
    vector<ui64>excess;
    const ui64 INF = 1e16;
    void gap(ui32 currentHeight);
    void push(DoubleEdge* edge);
    void relabel(ui32 vertex);
    void discharge(ui32 vertex);
    void allPushFrom(ui32 vertex);
public:
    PushRelabel(Network &_network);
    void findMaxFlow();
};
#endif
