#include "playerheader.h"
#include <vector>

using namespace std;

vector<int> playerheader::getHand()
{
    return hand;
}

int playerheader::getCash()
{
    return cash;
}

void playerheader::giveOrTakeCash(int amount)
{
    cash += amount;
}

void playerheader::Player()
{
    cash = 0;
}

void playerheader::~Player()
{
    cout <<"I am dead";
    delete this;
}