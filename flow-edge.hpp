#ifndef _FLOW_EDGE
#define _FLOW_EDGE

#include "edge.hpp"

class FlowEdge: public Edge {
public:
    ui32 capacity;
    i32 flow;
    FlowEdge* reversedEdge;
};

#endif
