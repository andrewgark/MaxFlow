#ifndef _MALHOTRA_KUMAR_MAHESHWARI_
#define _MALHOTRA_KUMAR_MAHESHWARI_

#include <queue>
#include "max-flow-solver.hpp"
#include "graph.hpp"

class MalhotraKumarMaheshwari: public MaxFlowSolver {
    ui32 numberVertices;
    vector<bool> deleted;
    vector<ui32> currentEdge, color;
    vector<ui64> potential, inPotential, outPotential;
    const ui64 INF = 1e16;
    void updatePotential(ui32 vertex);
    void calculatePotential(ui32 vertex);
    vector<ui32> blockingBFS(ui32 vertex);
    void sendFlow(ui32 vertex, ui64 sizeFlow, bool toSource);
    void makeFlowThrough(ui32 vertex);
    void deleteVertex(ui32 vertex);
public:
    MalhotraKumarMaheshwari(Network &_network);
    void findMaxFlow();
};
#endif
