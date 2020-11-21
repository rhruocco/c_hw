#include "playerheader.h"

using namespace playerHeader;

vector<int> getHand()
{
    return hand;
}

int getCash()
{
    return cash;
}

void giveOrTakeCash(int amount)
{
    cash += amount;
}