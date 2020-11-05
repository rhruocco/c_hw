#include <string>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>


int * board;
int boardSize = 0;

//Taken from: https://gist.github.com/kstatz12/1675e6823134f0c4437734148a9dcce3
int * create_2d_array()
{
    return (int*)malloc(boardSize * boardSize *sizeof(int));
}

//The further south, the greater the row value
//The further east, the greater the column value
bool checker(int shipSize, int currentRow, int currentCol, char direction)
{
    //this bool will be returned at the end. it'll remain true until something makes it false
    bool canSpawn = true;

    //These are calculated below
    //These are parameters for two loops that check if there's a ship 3 spaces away
    //from the ship it's currently checking thats aligned the same (vertically or horizontal)
    int threeAwayFromFirstPiece = 0;
    int threeAwayFromLastPiece = 0;

    
    //this switch statement changes the values above based on which direction the ship will spawn in.
    switch(direction)
    {
        case 'n':

        //for (int i = currentRow; i >= )
        break;

        case 's':
        break;

        case 'e':
        break;

        case 'w':
        break;

        default:
        break;
    }
    return canSpawn;
}

//this calls each direction's check to see which directions a ship can spawn in given its coordinates
char * checkAvaliableDirections(int shipSize, int currentRow, int currentCol)
{
    //a list of all the directions
    char directions [] = {'n','s','e','w'};
    for (int i = 0; i < 4; i++)
    {
        if (!checker(shipSize, currentRow, currentCol, directions[i]))
        {
            directions[i] = 'x';
            //replacing a direction with an x means that it cant spawn a ship in that direction.
        }
    }

    //it returns the modified directions list, with all the non-spawnable directions replaced with an x
    return directions;
}

bool shipsLeft(int * ships)  //checks if any ships are left to spawn
{
    bool shipsLeft = false;
    for(int i = 0; i < 5; i++)
    {
        if (ships[i] != 0)
        {
            shipsLeft = true;
        }
    }

    return shipsLeft;
}

//spawns a ship based on the passed in direction, by going through a loop and changing the 0's to 1's
void spawnShip(int currentRow, int currentCol, int shipToSpawn, char direction)
{
    //the row or col (depending on the direction the ship's spawning) of the last piece
    int lastPiece = 0;
    std::cout <<"\nspawnShip\n";
    switch (direction)
    {
        case 'n':
            lastPiece = currentRow - shipToSpawn + 1;
            for (int i = currentRow; i >= lastPiece; i--)
            {
                *(board + i* boardSize + currentCol) = 1;
            }
        break;

        case 's':
            lastPiece = currentRow + shipToSpawn - 1;
            for (int i = currentRow; i <= lastPiece; i++)
            {
                *(board + i* boardSize + currentCol) = 1;
            }
        break;

        case 'e':
            lastPiece = currentCol + shipToSpawn - 1;
            for (int j = currentCol; j <= lastPiece; j++)
            {
                *(board + currentRow * boardSize + j) = 1;
            }
        break;

        case 'w':
            lastPiece = currentCol - shipToSpawn + 1;
            for (int j = currentCol; j >= lastPiece; j--)
            {
                *(board + currentRow * boardSize + j) = 1;
            }
        break;

        default:
        break;
    }
  }

//big method for putting every ship on the board
void shipGen()
{
    char * avalDirections = new char;
    //The 5 ships are: Carrier (occupies 5 spaces), Battleship (4), Cruiser (3), Submarine (3), and Destroyer (2).
    int ships[5] = {5,4,3,3,2};
    int shipSpawnRng = 56;
    int randoSpawnDirectionIndex = 0;

    int randoShipsIndex = 0;

    //this loop checks every spot on the board
    for(int i = 0; i < boardSize; i++)
    {
        for (int j  = 0; j < boardSize; j++)
        {
            
            shipSpawnRng--;

            //only does this if based on rng and if there's any ships left
            if (shipSpawnRng > 50 && shipsLeft(ships))
            {
                //this picks a random ship from the list. the while loop runs until it picks a non 0 value
                
                //while (ships[randoShipsIndex] == 0)
                //{
                    randoShipsIndex = rand() % 4;
                    
                //}

                //creates a list that avaliableFunctions fills with all the directions the current ship can spawn in.
                //The current ship is whereever the loop is currently at, based on the row and colum index
                //Ships are spawned on one spot, then extended east, west, south, or north depending on their size
                
                avalDirections = checkAvaliableDirections(ships[randoShipsIndex],i,j);

                //calls the spawn check function to see if a ship has directions it can spawn that arent forbidden on this current spot,
                //as checked by the avalDirections above

                //similar randomization process to the randoShipIndex variable above, only for an index for the array of allowed directions
                randoSpawnDirectionIndex = rand() % 3;

                //calls the spawnShip function to begin the spawning process at wherever the loop is at. (represented by i for row and j for col)
                //then, that ship is given a value of 0 in the ships array so it doesnt get spawned again

                    spawnShip(i, j, ships[randoShipsIndex], avalDirections[randoSpawnDirectionIndex]);
                    ships[randoShipsIndex] = 0;
            }
            
        }
    }
}


//modified from: https://gist.github.com/kstatz12/1675e6823134f0c4437734148a9dcce3
void printBoard()
{
    std::cout <<"\n";
    //iterates thru the board and prints each space
    for(int i = 0; i < boardSize; i++)
    {
        for(int j = 0; j < boardSize; j++)
        {
           std::cout << *(board + i * boardSize + j) <<" ";
        }
        std::cout << std::endl;
    }
     std::cout << "Let's Play Battlship!\n";
}



int main()
{
    //the player is asked for a board size, then the board is generated, given ships, and printed.
    
    std::cout << "How big do you want the board to be?\nEnter 1 number, boards will be square:";

    std::cin >> boardSize;

    std::cout << std::endl;
    
    board = create_2d_array();
    srand (time(NULL));

    shipGen();
    printBoard();

    return 0;
} 
// gcc battleship2.cpp -lstdc++