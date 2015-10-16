#include <vector>
#include "graph.h"


class SimpleFor {
    Network network;
    ui32 numberVertices;
    vector < ui32 > currentEdge, height;
    vector < ui64 > excess;

    void push(Edge* edge) {
        ui32 sizePush = min(excess[edge->getBegin()], edge->getPushCapacity());
        if (edge->getReversed())
        {
            edge->getReversedEdge()->setFlow(edge->getReversedEdge()->getFlow() - sizePush);
            edge->setCapacity(edge->getCapacity() - sizePush);
        } else {
            edge->setFlow(edge->getFlow() + sizePush);
            edge->getReversedEdge()->setCapacity(edge->getReversedEdge()->getCapacity() + sizePush);
        }
        excess[edge->getBegin()] -= sizePush;
        excess[edge->getEnd()] += sizePush;
    }

    void relabel(ui32 vertex) {
        ui32 minv = numberVertices;
        for (ui32 numberEdge = 0; numberEdge < network.getDegree(vertex); ++numberEdge)
            if (network.getEdge(vertex, numberEdge)->getPushCapacity() > 0)
                if (minv == numberVertices || height[network.getEdge(vertex, numberEdge)->getEnd()] < height[minv])
                    minv = network.getEdge(vertex, numberEdge)->getEnd();
        height[vertex] = height[minv] + 1;
    }

    void discharge(ui32 vertex) {
        while (excess[vertex] > 0)
            if (currentEdge[vertex] < network.getDegree(vertex)) {
                if (height[network.getEdge(vertex, currentEdge[vertex])->getEnd()] + 1 == height[vertex])
                    push(network.getEdge(vertex, currentEdge[vertex]));
                currentEdge[vertex]++;
            } else {
                relabel(vertex);
                currentEdge[vertex] = 0;
            }
    }

    void allPushFrom(ui32 vertex) {
        for (ui32 numberEdge = 0; numberEdge < network.getDegree(vertex); ++numberEdge)
            push(network.getEdge(vertex, numberEdge));
    }
public:
    SimpleFor(Network &_network) : network(_network), numberVertices(_network.getNumberVertices()) {}

    void findMaxFlow() {
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
};
