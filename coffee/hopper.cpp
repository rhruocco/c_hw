#include <iostream>

#include "hopper.h"

//Returns beans
int Hopper::getBeans()
{
    return beans;
}

//grinds the beans
int Hopper::grind()
{
    while (beans > 0)
    {
        cout <<"\n"<<beans<<" Beans left to grind...\n";
        beans -= 25;
    }
    cout <<"\nDone grinding!\n";
}

//Constructor. Takes in the amount of water passed into the hopper and multiplies by 50 to get the beans needed
Hopper::Hopper(int cups)
{
    beans = cups * 50;
    cout << "\nLoading "<<beans<<" beans...";
}

//Destructor
Hopper::~Hopper()
{

}