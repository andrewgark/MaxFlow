#include <vector>

#include "max-flow-solver.hpp"
#include "push-relabel.hpp"
#include "graph.hpp"

void PushRelabel::gap(ui32 currentHeight) {
    for (ui32 currentVertex = 0; currentVertex < numberVertices; ++currentVertex)
        if ((currentHeight < height[currentVertex]) && (height[currentVertex] < numberVertices)) {
            sizeHeight[height[currentVertex]]--;
            height[currentVertex] = numberVertices;
            sizeHeight[height[currentVertex]]++;
        }
}

void PushRelabel::push(DoubleEdge* edge) {
    ui32 sizePush = edge->push(excess[edge->getBegin()]);
    excess[edge->getBegin()] -= sizePush;
    excess[edge->getEnd()] += sizePush;
}

void PushRelabel::relabel(ui32 vertex) {
    ui32 minv = numberVertices;
    sizeHeight[height[vertex]]--;
    for (ui32 numberEdge = 0; numberEdge < network.getDegree(vertex); ++numberEdge)
        if (network.getEdge(vertex, numberEdge)->getCapacity() > 0)
            if (minv == numberVertices || height[network.getEdge(vertex, numberEdge)->getEnd()] < height[minv])
                minv = network.getEdge(vertex, numberEdge)->getEnd();
    height[vertex] = height[minv] + 1;
    sizeHeight[height[vertex]]++;
}

void PushRelabel::discharge(ui32 vertex) {
    while (excess[vertex] > 0)
        if (currentEdge[vertex] < network.getDegree(vertex)) {
            if (height[network.getEdge(vertex, currentEdge[vertex])->getEnd()] + 1 == height[vertex])
                push(network.getEdge(vertex, currentEdge[vertex]));
            currentEdge[vertex]++;
        } else {
            if (sizeHeight[height[vertex]] == 1)
                gap(height[vertex]);
            relabel(vertex);
            currentEdge[vertex] = 0;
        }
}

void PushRelabel::allPushFrom(ui32 vertex) {
    for (ui32 numberEdge = 0; numberEdge < network.getDegree(vertex); ++numberEdge)
        push(network.getEdge(vertex, numberEdge));
}

PushRelabel::PushRelabel(Network &_network) : MaxFlowSolver(_network), numberVertices(_network.getNumberVertices()) {}

void PushRelabel::findMaxFlow() {
    sizeHeight.resize(2 * numberVertices + 2, 0);
    sizeHeight[0] = numberVertices - 1;
    sizeHeight[numberVertices] = 1;
    height.resize(numberVertices, 0);
    height[network.getSource()] = numberVertices;
    excess.resize(numberVertices, 0);
    excess[network.getSource()] = INF;
    currentEdge.resize(numberVertices, 0);
    bool can = true;
    allPushFrom(network.getSource());
    while (can) {
        can = false;
        for (ui32 vertex = 0; vertex < numberVertices; ++vertex)
            if (excess[vertex] > 0 && vertex != network.getSource() && vertex != network.getSink()) {
                can = true;
                discharge(vertex);
            }
    }
}

