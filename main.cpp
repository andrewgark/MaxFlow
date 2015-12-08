#include <iostream>
#include "malhotra-kumar-maheshwari.hpp"
#include "push-relabel.hpp"

int main()
{
    Network network;
    cin >> network;
    //PushRelabel pushRelabel(network);
    //pushRelabel.findMaxFlow();
    MalhotraKumarMaheshwari malhotraKumarMaheshwari(network);
    malhotraKumarMaheshwari.findMaxFlow();
    cout << network;
    return 0;
}
