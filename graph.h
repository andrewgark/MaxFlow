#pragma once

using namespace std;

typedef unsigned long long ui32;
typedef unsigned long long ui64;

class IEdge {
public:
    virtual void getBegin() = 0;
    virtual void getEnd() = 0;
};

class IFlowEdge {
public:
    ui32 capacity;
    ui32 flow;
    bool reversed;
    IFlowEdge* reversedEdge;
};

class IGraph {
public:
    virtual ui32 getNumberVertices() = 0;
    virtual ui32 getDegree(ui32 vertex) = 0;
    virtual void read(istream &in) = 0;
};


class INetwork: public IGraph {
public:
    virtual ui32 getSource() = 0;
    virtual ui32 getSink() = 0;
    virtual void printFlowById(ostream& out) = 0;
    virtual void printAnswer(ostream& out) = 0;
};
