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
        beans -= 25;
        cout <<"\n"<<beans<<" Beans left to grind...\n";
    }
    cout <<"\nDone grinding!";
}
