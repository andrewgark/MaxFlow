#include <queue>
#include "max-flow-solver.h"
#include "graph.cpp"

class MalhotraKumarMaheshwari: public IMaxFlowSolver {
    Network network;
    ui32 numberVertices;
    vector < bool > deleted;
    vector < ui32 > currentEdge, color;
    vector < ui64 > potential, inPotential, outPotential;
    const ui64 INF = 1e16;

    void updatePotential(ui32 vertex) {
        potential[vertex] = min(inPotential[vertex], outPotential[vertex]);
    }

    void calculatePotential(ui32 vertex) {
        inPotential[vertex] = (vertex == network.getSource()) ? INF : 0;
        outPotential[vertex] = (vertex == network.getSink()) ? INF : 0;
        for (ui32 currentEdge = 0; currentEdge < network.getDegree(vertex); ++currentEdge) {
            Edge* thisEdge = network.getEdge(vertex, currentEdge);
            if (color[vertex] == color[thisEdge->getEnd()] + 1)
                inPotential[vertex] += thisEdge->reversedEdge->getCapacity();
            else if (color[vertex] + 1 == color[thisEdge->getEnd()])
                outPotential[vertex] += thisEdge->getCapacity();
        }
        updatePotential(vertex);
    }

    void blockingBFS(ui32 vertex) {
        color = vector < ui32 > (numberVertices, numberVertices);
        queue < ui32 > queueBFS;
        queueBFS.push(vertex);
        color[vertex] = 0;
        while (!queueBFS.empty()) {
            ui32 currentVertex = queueBFS.front();
            queueBFS.pop();
            for (ui32 currentEdge = 0; currentEdge < network.getDegree(currentVertex); ++currentEdge) {
                Edge* thisEdge = network.getEdge(currentVertex, currentEdge);
                if (color[thisEdge->getEnd()] == numberVertices && thisEdge->getCapacity() > 0) {
                    color[thisEdge->getEnd()] = color[currentVertex] + 1;
                    queueBFS.push(thisEdge->getEnd());
                }
            }
        }
    }

    void sendFlow(ui32 vertex, ui64 sizeFlow, bool toSource) {
        queue < ui32 > queueFlow;
        vector < ui64 > extra(numberVertices, 0);
        queueFlow.push(vertex);
        extra[vertex] = sizeFlow;

        while (!queueFlow.empty()) {
            ui32 currentVertex = queueFlow.front();
            queueFlow.pop();
            if (toSource)
                inPotential[currentVertex] -= extra[currentVertex];
            else
                outPotential[currentVertex] -= extra[currentVertex];
            updatePotential(currentVertex);
            if (toSource && currentVertex == network.getSource())
                return;
            if (!toSource && currentVertex == network.getSink())
                return;
            while (extra[currentVertex] > 0) {
                ui32 nextVertex = network.getEdge(currentVertex, currentEdge[currentVertex])->getEnd();
                Edge* thisEdge;
                bool edgeIsOk = false;
                if (toSource && !deleted[nextVertex] && color[nextVertex] + 1 == color[currentVertex]) {
                    thisEdge = network.getEdge(currentVertex, currentEdge[currentVertex])->reversedEdge;
                    edgeIsOk = true;
                }
                else if (!toSource && !deleted[nextVertex] && color[nextVertex] == color[currentVertex] + 1) {
                    thisEdge = network.getEdge(currentVertex, currentEdge[currentVertex]);
                    edgeIsOk = true;
                }
                if (edgeIsOk) {
                    ui32 curSizePush = thisEdge->push(extra[currentVertex]);
                    if (extra[nextVertex] == 0)
                        queueFlow.push(nextVertex);
                    extra[nextVertex] += curSizePush;
                    extra[currentVertex] -= curSizePush;
                    if (toSource)
                        outPotential[nextVertex] -= curSizePush;
                    else
                        inPotential[nextVertex] -= curSizePush;
                    updatePotential(nextVertex);
                }
                currentEdge[currentVertex] = (currentEdge[currentVertex] + 1) % network.getDegree(currentVertex);
            }
        }
    }

    void makeFlowThrough(ui32 vertex) {
        ui64 sizeFlow = potential[vertex];
        sendFlow(vertex, sizeFlow, 1);
        sendFlow(vertex, sizeFlow, 0);
    }

    void deleteVertex(ui32 vertex) {
        deleted[vertex] = 1;
        for (ui32 i = 0; i < network.getDegree(vertex); ++i) {
            Edge* thisEdge = network.getEdge(vertex, i);
            if (color[thisEdge->getEnd()] == color[vertex] + 1)
                inPotential[thisEdge->getEnd()] -= thisEdge->getCapacity();
            else if ((color[thisEdge->getEnd()] + 1 == color[vertex]))
                outPotential[thisEdge->getEnd()] -= thisEdge->reversedEdge->getCapacity();
            updatePotential(thisEdge->getEnd());
        }
    }
public:
    MalhotraKumarMaheshwari(Network &_network) :
        network(_network), numberVertices(_network.getNumberVertices()) {}

    void findMaxFlow() {
        bool can = true;
        potential.resize(numberVertices);
        inPotential.resize(numberVertices);
        outPotential.resize(numberVertices);
        while (can) {
            can = false;
            blockingBFS(network.getSource());
            if (color[network.getSink()] != numberVertices)
                can = true;
            currentEdge = vector < ui32 > (numberVertices, 0);
            deleted = vector < bool > (numberVertices, false);
            for (ui32 vertex = 0; vertex < numberVertices; vertex++) {
                calculatePotential(vertex);
            }

            for (ui32 i = 0; i < numberVertices; ++i) {
                ui32 keyVertex = numberVertices + 1;
                for (ui32 vertex = 0; vertex < numberVertices; ++vertex)
                    if (!deleted[vertex] && (keyVertex == numberVertices + 1 || potential[vertex] < potential[keyVertex]))
                        keyVertex = vertex;
                if (potential[keyVertex] != 0)
                    makeFlowThrough(keyVertex);
                deleteVertex(keyVertex);
            }
        }
    }
};
