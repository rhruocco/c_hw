#include <iostream>
#include <stdio.h>
#include <cstdlib>

#include "reservoir.h"
#include "hopper.h"

using namespace std;

Reservoir res;
Hopper hop(res.getCups());

int main()
{
   hop.grind();
   res.boil(); 
}