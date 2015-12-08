#ifndef _DOUBLE_EDGE
#define _DOUBLE_EDGE

#include "flow-edge.hpp"

class DoubleEdge: public FlowEdge {
    ui32 begin, end;
public:
    ui32 capacity;
    ui32 flow;
    DoubleEdge* reversedEdge;
    DoubleEdge(ui32 _begin, ui32 _end, ui32 _capacity);
    DoubleEdge(ui32 _begin, ui32 _end, ui32 _capacity, DoubleEdge* _reversedEdge);
    ui32 getBegin();
    ui32 getEnd();
    ui32 getCapacity();
    ui32 push(ui32 wantedSizePush);
};

#endif
