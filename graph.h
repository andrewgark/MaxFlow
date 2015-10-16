#pragma once
#include <vector>

using namespace std;

typedef unsigned long long ui32;
typedef unsigned long long ui64;

const ui64 INF = 1000000000000000000;

class Edge {
    ui32 begin, end, capacity, flow;
    Edge* reversedEdge;
    bool reversed;
public:
    Edge(ui32 _begin, ui32 _end, ui32 _capacity, bool _reversed)
        : begin(_begin), end(_end), capacity(_capacity), reversed(_reversed), flow(0) {}

    Edge(ui32 _begin, ui32 _end, ui32 _capacity, bool _reversed, Edge* _reversedEdge)
        : begin(_begin), end(_end), capacity(_capacity), reversed(_reversed), reversedEdge(_reversedEdge), flow(0) {}

    void setReversedEdge(Edge* _reversedEdge) {
        reversedEdge = _reversedEdge;
    }

    void setCapacity(ui32 _capacity) {
        capacity = _capacity;
    }

    void setFlow(ui32 _flow) {
        flow = _flow;
    }

    ui32 getFlow() {
        return flow;
    }

    ui32 getBegin() {
        return begin;
    }

    ui32 getEnd() {
        return end;
    }

    ui32 getCapacity() {
        return capacity;
    }

    Edge* getReversedEdge() {
        return reversedEdge;
    }

    bool getReversed() {
        return reversed;
    }

    ui32 getPushCapacity() {
        return capacity - flow;
    }
};

class Network {
    ui32 numberVertices, numberEdges;
    ui32 source, sink;

    vector < vector < Edge* > > edges;
    vector < Edge* > edgesById;
public:
    Network(ui32 _numberVertices, ui32 _source, ui32 _sink) : numberVertices(_numberVertices),
            source(_source), sink(_sink) {
        edges.resize(numberVertices);
        numberEdges = 0;
    }

    void addEdge(ui32 edgeBegin, ui32 edgeEnd, ui32 edgeCapacity)
    {
        numberEdges++;
        Edge *directEdge = new Edge(edgeBegin, edgeEnd, edgeCapacity, 0);
        Edge *reversedEdge = new Edge(edgeEnd, edgeBegin, 0,  1, directEdge);
        directEdge->setReversedEdge(reversedEdge);
        reversedEdge->setReversedEdge(directEdge);
        edgesById.push_back(directEdge);
        edges[edgeBegin].push_back(directEdge);
        edges[edgeEnd].push_back(reversedEdge);
    }

    Edge* getEdge(ui32 vertex, ui32 edge) {
        return edges[vertex][edge];
    }

    ui32 getDegree(ui32 vertex) {
        return edges[vertex].size();
    }

    void printFlowById() {
        for (ui32 edgeId = 0; edgeId < numberEdges; ++edgeId)
            cout << edgesById[edgeId]->getFlow() << "\n";
    }

    void printAnswer() {
        ui64 answer = 0;
        for (ui32 currentEdge = 0; currentEdge < getDegree(source); ++currentEdge) {
            answer += getEdge(source, currentEdge)->getFlow();
        }
        cout << answer << "\n";
    }

    ui32 getSource() {
        return source;
    }

    ui32 getSink() {
        return sink;
    }

    ui32 getNumberVertices() {
        return numberVertices;
    }
};
