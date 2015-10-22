#pragma once
#include <vector>
#include <iostream>
#include "graph.h"

class Edge: public IFlowEdge {
    ui32 begin, end;
public:
    bool reversed;
    ui32 capacity, flow;
    Edge* reversedEdge;
    Edge(ui32 _begin, ui32 _end, ui32 _capacity, bool _reversed)
        : begin(_begin), end(_end), capacity(_capacity), reversed(_reversed), flow(0) {}

    Edge(ui32 _begin, ui32 _end, ui32 _capacity, bool _reversed, Edge* _reversedEdge)
        : begin(_begin), end(_end), capacity(_capacity), reversed(_reversed), reversedEdge(_reversedEdge), flow(0) {}

    ui32 getBegin() {
        return begin;
    }

    ui32 getEnd() {
        return end;
    }

    ui32 getPushCapacity() {
        return capacity - flow;
    }
};

class Network: public INetwork {
    ui32 numberVertices, numberEdges;
    ui32 source, sink;

    void addEdge(ui32 edgeBegin, ui32 edgeEnd, ui32 edgeCapacity)
    {
        numberEdges++;
        Edge *directEdge = new Edge(edgeBegin, edgeEnd, edgeCapacity, 0);
        Edge *reversedEdge = new Edge(edgeEnd, edgeBegin, 0,  1, directEdge);
        directEdge->reversedEdge = reversedEdge;
        reversedEdge->reversedEdge = directEdge;
        edgesById.push_back(directEdge);
        edges[edgeBegin].push_back(directEdge);
        edges[edgeEnd].push_back(reversedEdge);
    }

    vector < vector < Edge* > > edges;
    vector < Edge* > edgesById;
public:
    void read(istream &in) {
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

    Edge* getEdge(ui32 vertex, ui32 edgeID) {
        return edges[vertex][edgeID];
    }

    ui32 getDegree(ui32 vertex) {
        return edges[vertex].size();
    }

    void printFlowById(ostream& out) {
        for (ui32 edgeId = 0; edgeId < numberEdges; ++edgeId)
            out << edgesById[edgeId]->flow << "\n";
    }

    void printAnswer(ostream& out) {
        ui64 answer = 0;
        for (ui32 currentEdge = 0; currentEdge < getDegree(source); ++currentEdge) {
            answer += getEdge(source, currentEdge)->flow;
        }
        out << answer << "\n";
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

    friend istream& operator >> (istream& in, Network& network) {
        network.read(in);
        return in;
    }

    friend ostream& operator << (ostream& out, Network& network) {
        network.printAnswer(out);
        network.printFlowById(out);
        return out;
    }
};
