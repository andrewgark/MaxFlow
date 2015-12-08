#ifndef _MAX_FLOW_SOLVER
#define _MAX_FLOW_SOLVER

#include "network.hpp"

class MaxFlowSolver {
public:
    virtual void findMaxFlow() = 0;
    Network network;
    MaxFlowSolver(Network &network_);
};
#endif
