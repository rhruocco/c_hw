#include <iostream>
#include <stdio.h>
#include "playerheader.h"
#include <vector>
#include <ctime>

using namespace std;

Player playa, dealer;

void game()
{
    int bet = 0;
    int randomIndex = 0;
    vector<int> deck = {1,2,3,4,5,6,7,8,9,10,10,10,1,2,3,4,5,6,7,8,9,10,10,10,1,2,3,4,5,6,7,8,9,10,10,10,1,2,3,4,5,6,7,8,9,10,10,10,};
    
    randomIndex = rand() % deck.size() + 1;

    dealer.draw(deck[randomIndex]);


}

int main()
{
    for (int i = 0; i < 100; i++)
    {
        game();
    }
    return 0;
}

// gcc blackjack.cpp player.cpp -lstdc++