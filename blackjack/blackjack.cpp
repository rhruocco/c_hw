#include <iostream>
#include <stdio.h>
#include "playerheader.h"
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

Player playa, dealer;
vector<int> deck;

//chooses a random card from the deck to deal. also removes that card from the deck
int deal()
{
    int randomIndex = 0;
    randomIndex = rand() % deck.size() + 1;

    int cardDealt = deck[randomIndex];
    deck.erase(deck.begin() + randomIndex - 1);
    return cardDealt;
}

//empties, then refills the deck. called at round starts
void resetDeck()
{
    //erases the current deck
    for (int i = 0; i < deck.size(); i++)
    {
        deck.erase(deck.begin() + i);
    }

    //fills the deck. possibly a dumb way to do this
    for (int i = 0; i < 4; i++)
    {
        for(int g = 1; g <= 10; g++)
        {
            deck.push_back(g);
        }
    }    
}

//logic for deciding whether or not the player will hit
bool shouldIHit()
{
    int pSum = playa.getSum();
    int dSum = dealer.getSum();
    if (pSum > dSum || pSum == 21)
    {
        return false;
    }
    if (pSum == dSum)
    {
    } 

}

//the gameplay method, called 100 times OR until someone busts
void game()
{
    int bet = playa.getCash() / 10;
    
    resetDeck();

    dealer.draw(deal());
    int faceDownDealerCard = deal();

    playa.draw(deal());
    playa.draw(deal());

    if(shouldIHit)
    {
        playa.draw(deal());
    }
    dealer.draw(faceDownDealerCard);

}



int main()
{
    deck.reserve(52);
    for (int i = 0; i < 100; i++)
    {
        game();
    }
    return 0;
}

// gcc blackjack.cpp player.cpp -lstdc++