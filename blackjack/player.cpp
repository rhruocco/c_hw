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

//resets the players deck. also sets the sum to zero
void Player::resetDeck()
{
    for (int i = 0; i < hand.size(); i++)
    {
        hand.erase(hand.begin() + i);
    }
    sum = 0;
}


// Adjusts the player's cash. Called when they either win or lose money. If they lose, a negative int is passed in
void Player::giveOrTake(int amount)
{
    cash += amount;
}

//Player constructor, sets cash to starting amount
Player::Player()
{
    hand.reserve(10);
    cash = 1000;
}

//Player destructor
Player::~Player()
{
}

//adds a card to the player's hand
void Player::draw(int card)
{
    hand.push_back(card);
    calcSum();
}

//returns the sum of the player's current hand
int Player::getSum()
{
    return sum;
}

//calculates the sum of the player's current hand
void Player::calcSum()
{
    int aces = 0;
    sum = 0;
    //adds every card together, except for aces, which is done below seperately
    for (int i = 0; i < hand.size(); i++)
    {
        if (hand[i] == (1 || 11))
        {
            aces++;
        }
        else
        {
            
            sum += hand[i];
        }
    }

    //adds any aces (represented as 1's) seperately to determine whether they should be counted as 1's or 11's
    for (int a = 0; a < aces; a++)
    {
        if((11 + sum) <= 21)
        {
            sum += 11;
        }
        else
        {
            sum++;
        }
    }
}