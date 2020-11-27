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
        //this determines how likely the player is to hit based on how close they are to busting
        int riskiness = 0;

        switch(pSum)
        {
            case 17:
            riskiness = 85;
            break;
            case 18:
            riskiness = 55;
            break;
            case 19:
            riskiness = 15;
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
        else
        {
            return false;
        }
    }

    if (pSum < dSum)
    {
        return true;
    }
}

//checks to see if the game is over, and awards the bet based on its outcome if so. returns true if game's over
bool isGameOver(int bet)
{
    int dSum = dealer.getSum();
    int pSum = playa.getSum();
    if (dSum > 21)
    {
        if(pSum <= 21)
        {
            wins++;
           playa.giveOrTake(bet);
        }
           return true; 
    }

    if (pSum > 21)
    {
        if (dSum <= 21)
        {
            losses++;
            playa.giveOrTake(-bet);
        }

        return true;
    }

    if (dSum >= 17 && pSum > dSum)
    {
        wins++;
        playa.giveOrTake(bet);
        return true;
    }

    return false;
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

    while (!isGameOver(bet))
    {

    if (shouldIHit)
    {
        playa.draw(deal());
    }

    if (dealer.getSum() < 17)
    {
        dealer.draw(deal());
    }
    }
}



int main()
{
    srand(time(NULL));
    
    deck.reserve(52);
    for (int i = 0; i < 100; i++)
    {
        game();
    }
    if (playa.getCash() > 0)
    {
    cout << "The Player ended with $"<<playa.getCash();
    }
    else
    {
        cout << "The Player went broke!";
    }
    cout <<"\nWins: "<<wins<<"\nTies: "<<ties<<"\nLosses: "<<losses;
    
    return 0;
}

// gcc blackjack.cpp player.cpp -lstdc++