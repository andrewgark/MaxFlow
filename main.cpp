#include <iostream>
#include "mkm.h"
#include "simplefor.h"

int main()
{
    ui32 numberVertices, numberEdges;
    cin >> numberVertices >> numberEdges;
    Network network(numberVertices, 0, numberVertices - 1);
    for (ui32 edgeId = 0; edgeId < numberEdges; ++edgeId)
    {
        ui32 edgeBegin, edgeEnd, edgeCapacity;
        cin >> edgeBegin >> edgeEnd >> edgeCapacity;
        edgeBegin--;
        edgeEnd--;
        network.addEdge(edgeBegin, edgeEnd, edgeCapacity);
    }
    SimpleFor simpleFor(network);
    simpleFor.findMaxFlow();
    //MKM mkm(network);
    //mkm.findMaxFlow();
    network.printAnswer();
    network.printFlowById();
    return 0;
}
