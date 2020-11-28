#include <iostream>
#include <stdio.h>
#include "playerheader.h"
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

Player playa, dealer;
vector<int> deck;
int wins, losses, ties = 0;

//chooses a random card from the deck to deal. also removes that card from the deck
int deal()
{
    int randomIndex = rand() % deck.size() + 1;

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
    //this determines how likely the player is to hit based on how close they are to busting
    if (pSum >= 21)
    {
        return false;
    }
    int riskiness = 0;

    switch(pSum)
    {
        case 15:
        riskiness = 60;
        break;
        case 16:
        riskiness = 55;
        break;
        case 17:
        riskiness = 50;
        break;
        case 18:
        riskiness = 35;
        break;
        case 19:
        riskiness = 5;
        break;
        case 20:
        riskiness = 2;
        break;
        case 21:
        riskiness = 0;
        break;

        default:
        riskiness = 100;
        break;
    }

    //randomly determines whether or not to hit based on riskiness
    int hitRng = rand() % 101;
    if (hitRng <= riskiness)
    {
        return true;
    }

    return false;
}

//determines who wins, updates game stats and assigns bets accordinglly
void whoWins(int bet)
{
    int dSum = dealer.getSum();
    int pSum = playa.getSum();

    if (pSum > 21 || dSum > 21)
    {
        if (pSum <= 21)
        {
            wins++;
            playa.giveOrTake(bet);
        }
        else if (dSum <= 21)
        {
            losses++;
            playa.giveOrTake(-bet);
        }
        else
        {
            ties++;
        }
        return; 
    }
    
    if (pSum < dSum)
    {
        losses++;
        playa.giveOrTake(-bet);
        return;
    }

    if (pSum > dSum)
    {
        wins++;
        playa.giveOrTake(bet);
        return;
    }

    if (pSum == dSum)
    {
        ties++;
        return;
    }

}

//the gameplay method, called 100 times OR until someone busts
void game()
{
    int bet = playa.getCash() / 10 + (rand() % 11);
    
    resetDeck();

    dealer.draw(deal());
    int faceDownDealerCard = deal();

    playa.draw(deal());
    playa.draw(deal());

    while (shouldIHit())
    {
        playa.draw(deal());
    }

    dealer.draw(faceDownDealerCard);
    while (dealer.getSum() < 17)
    {
        dealer.draw(deal());
    }

    whoWins(bet);

    dealer.resetDeck();
    playa.resetDeck();
}

int main()
{
    srand (time(NULL));
    deck.reserve(52);
    for (int i = 0; i < 100; i++)
    {
        game();
        if (playa.getCash() <= 0)
        {
            i = 100;
        }
    }

    if (playa.getCash() > 0)
    {
    cout << "The Player ended with $"<<playa.getCash();
    }
    else
    {
        cout << "The Player went broke!";
    }
    cout <<"\nWins: "<<wins<<"\nTies: "<<ties<<"\nLosses: "<<losses<<"\n";
  
    return 0;
}