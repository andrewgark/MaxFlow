#include "network.hpp"
#include <queue>

void Network::addEdge(ui32 edgeBegin, ui32 edgeEnd, ui32 edgeCapacity) {
    numberEdges++;
    DoubleEdge *directEdge = new DoubleEdge(edgeBegin, edgeEnd, edgeCapacity);
    DoubleEdge *reversedEdge = new DoubleEdge(edgeEnd, edgeBegin, 0, directEdge);
    directEdge->reversedEdge = reversedEdge;
    reversedEdge->reversedEdge = directEdge;
    edgesById.push_back(directEdge);
    edges[edgeBegin].push_back(directEdge);
    edges[edgeEnd].push_back(reversedEdge);
}

vector<ui32> Network::blockingBFS(ui32 vertex) {
    vector<ui32> BFSColor(numberVertices, numberVertices);
    queue<ui32> queueBFS;
    queueBFS.push(vertex);
    BFSColor[vertex] = 0;
    while (!queueBFS.empty()) {
        ui32 currentVertex = queueBFS.front();
        queueBFS.pop();
        for (ui32 currentEdge = 0; currentEdge < getDegree(currentVertex); ++currentEdge) {
            DoubleEdge* thisEdge = getEdge(currentVertex, currentEdge);
            if (BFSColor[thisEdge->getEnd()] == numberVertices && thisEdge->getCapacity() > 0) {
                BFSColor[thisEdge->getEnd()] = BFSColor[currentVertex] + 1;
                queueBFS.push(thisEdge->getEnd());
            }
        }
    }
    return BFSColor;
}

void Network::read(istream &in) {
    ui32 numberInEdges;
    in >> numberVertices >> numberInEdges;
    edges.resize(numberVertices);
    numberEdges = 0;
    for (ui32 edgeId = 0; edgeId < numberInEdges; ++edgeId)
    {
        ui32 edgeBegin, edgeEnd, edgeCapacity;
        in >> edgeBegin >> edgeEnd >> edgeCapacity;
        edgeBegin--;
        edgeEnd--;
        addEdge(edgeBegin, edgeEnd, edgeCapacity);
    }
    source = 0;
    sink = numberVertices - 1;
}

DoubleEdge* Network::getEdge(ui32 vertex, ui32 edgeID) {
    return edges[vertex][edgeID];
}

ui32 Network::getDegree(ui32 vertex) {
    return edges[vertex].size();
}

void Network::printFlowById(ostream& out) {
    for (ui32 edgeId = 0; edgeId < numberEdges; ++edgeId)
        out << edgesById[edgeId]->flow << "\n";
}

void Network::printAnswer(ostream& out) {
    i64 answer = 0;
    for (ui32 currentEdge = 0; currentEdge < getDegree(source); ++currentEdge) {
        answer += getEdge(source, currentEdge)->flow;
    }
    out << answer << "\n";
}

ui32 Network::getSource() {
    return source;
}

ui32 Network::getSink() {
    return sink;
}

ui32 Network::getNumberVertices() {
    return numberVertices;
}

istream& operator >> (istream& in, Network& network) {
    network.read(in);
    return in;
}

ostream& operator << (ostream& out, Network& network) {
    network.printAnswer(out);
    network.printFlowById(out);
    return out;
}
