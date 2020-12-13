#include <iostream>

#include "reservoir.h"

#include <typeinfo>

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
    cout<<"\nPouring "<<cups<<" cup(s).\n";
}

//Boils the water
void Reservoir::boil()
{
    while (temp < 180)
    {
        temp += 15;
        cout <<"\nWater is "<<temp<<" degrees...\n";
    }
    cout <<"\nDone boiling!";

    pour();
}

//Constructor
Reservoir::Reservoir()
{
    cout << "How many cups of Joe would you like?\n(No more than 4)\n";
    int dummy = 0;
    cin >> cups;

    //Wont let the user continue until they enter a number <= 4
    while (cups > 4)
    {
        cout << "\nIt can't hold that much.\nPlease enter a number, 1-4\n";
        cin >> cups;
    }
    cout <<"\nFilling "<<cups<<" cup(s).\n";
    
}

//Destructor
Reservoir::~Reservoir()
{

}