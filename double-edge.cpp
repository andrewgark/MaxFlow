#include <vector>
#include <iostream>
#include "double-edge.hpp"

DoubleEdge::DoubleEdge(ui32 _begin, ui32 _end, ui32 _capacity)
    : begin(_begin), end(_end), capacity(_capacity), flow(0) {}

DoubleEdge::DoubleEdge(ui32 _begin, ui32 _end, ui32 _capacity, DoubleEdge* _reversedEdge)
    : begin(_begin), end(_end), capacity(_capacity), reversedEdge(_reversedEdge), flow(0) {}

ui32 DoubleEdge::getBegin() {
    return begin;
}

ui32 DoubleEdge::getEnd() {
    return end;
}

ui32 DoubleEdge::getCapacity() {
    return capacity - flow;
}

ui32 DoubleEdge::push(ui32 wantedSizePush) {
    ui32 sizePush = min(wantedSizePush, getCapacity());
    flow += sizePush;
    reversedEdge->flow -= sizePush;
    return sizePush;
}


