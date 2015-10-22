#include <iostream>
#include "malhotra-kumar-maheshwari.cpp"
#include "push-relabel.cpp"

int main()
{
    ui32 numberVertices, numberEdges;
    Network network;
    cin >> network;
    PushRelabel pushRelabel(network);
    pushRelabel.findMaxFlow();
    //MalhotraKumarMaheshwari malhotraKumarMaheshwari(network);
    //malhotraKumarMaheshwari.findMaxFlow();
    cout << network;
    return 0;
}
