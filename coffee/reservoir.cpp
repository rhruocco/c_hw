#include <iostream>

#include "reservoir.h"

using namespace std;

//Returns the temp of the water
int Reservoir::getTemp()
{
  return temp;
}

//returns the amount of water
int Reservoir::getCups()
{
    return cups;
}

//Pours the cups of coffee when boiling is complete
void Reservoir::pour()
{
    cout<<"\nPouring "<<cups<<" cups.\n";
}

//Boils the water
void Reservoir::boil()
{
    while (temp > 180)
    {
        temp += 15;
        cout <<"\nWater is "<<temp<<" degrees...\n"
    }
    cout <<"\nDone boiling!";

    pour();
}

