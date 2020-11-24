#include "playerheader.h"
#include <vector>
#include <iostream>

using namespace std;


//Returns the player's current hand
vector<int> Player::getHand()
{
    return hand;
}

//Returns how much cash the player has
int Player::getCash()
{
    return cash;
}


// Adjusts the player's cash. Called when they either win or lose money. If they lose, a negative int is passed in
void Player::giveOrTake(int amount)
{
    cash += amount;
}

//Player constructor, sets cash to starting amount
Player::Player()
{
    cash = 1000;
}

//Player destructor
Player::~Player()
{
    //cout <<"I am dead";
    //delete this;
}