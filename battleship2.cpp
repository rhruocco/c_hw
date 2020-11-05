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

//This checker runs on each individual space of a ship's potential location.
//It returns whether or not the passed in space is safe to spawn on.
//It checks to make sure there are no ships within 3 spaces in all 4 directions, as well as its current location
//This method is called in a for loop in checker() below
bool spaceChecker(int currentRow, int currentCol)
{
    //checks to see if the space its been given is currentely occupied
    if (*(board + currentRow * boardSize + currentCol) == 1)
    {
        return false;
    }

    int loopBeginPoint;
    int loopEndPoint = 0;

    int threeEast = currentCol + 3;
    int threeWest = currentCol - 3;
    int threeNorth = currentRow - 3;
    int threeSouth = currentRow + 3;

    //Checks South of current location
    loopBeginPoint = currentRow + 1;
    loopEndPoint = currentRow + 3;
    for (int i = loopBeginPoint; i <= loopEndPoint; i++)
    {
        if (*(board + i * boardSize + currentCol) == 1)
        {
            return false;
        }
    }

    //Checks North of current location
    loopBeginPoint = currentRow - 1;
    loopEndPoint = currentRow -3;
    for (int i = loopBeginPoint; i >= loopEndPoint; i--)
    {
         if (*(board + i * boardSize + currentCol) == 1)
        {
            return false;
        }
    }

    //Checks East of current location
    loopBeginPoint = currentCol + 1;
    loopEndPoint = currentCol + 3;
    for (int j = loopBeginPoint; j <= loopEndPoint; j++)
    {
         if (*(board + currentRow * boardSize + j) == 1)
        {
            return false;
        }
    }

    //Checks West of current location
    loopBeginPoint = currentCol - 1;
    loopEndPoint = currentCol - 3;
    for (int j = loopBeginPoint; j >= loopEndPoint; j--)
    {
         if (*(board + currentRow * boardSize + j) == 1)
        {
            return false;
        }
    }
    return true;
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

    int lastPiece = 0;

    
    //this switch statement changes the values above based on which direction the ship will spawn in.
    switch(direction)
    {
        case 'n':

        lastPiece = currentRow - shipSize + 1; 
        if (lastPiece < 0)
        {
            return false;
        }

        for (int i = currentRow; i >= lastPiece;i--)
        {
            if (!spaceChecker(currentRow, currentCol))
            {
                return false;
            }
        }
        break;

        case 's':
        lastPiece = currentRow - shipSize + 1; 
        if (lastPiece > boardSize)
        {
            return false;
        }

        for (int i = currentRow; i <= lastPiece;i++)
        {
            if (!spaceChecker(currentRow, currentCol))
            {
                return false;
            }
        }
        break;

        case 'e':
        lastPiece = currentCol + shipSize - 1; 

        if (lastPiece > boardSize)
        {
            return false;
        }

        for (int j = currentCol; j <= lastPiece;j++)
        {
            if (!spaceChecker(currentRow, currentCol))
            {
                return false;
            }
        }
        break;

        case 'w':
        lastPiece = currentCol - shipSize + 1; 
        if (lastPiece < 0)
        {
            return false;
        }

        for (int j = currentCol; j >= lastPiece;j--)
        {
            if (!spaceChecker(currentRow, currentCol))
            {
                return false;
            }
        }
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
    int shipSpawnRng = 0;
    int randoSpawnDirectionIndex = 0;

    int randoShipsIndex = 0;

    //this loop checks every spot on the board
    for(int i = 0; i <= boardSize; i++)
    {
        for (int j  = 0; j <= boardSize; j++)
        {
            
            shipSpawnRng = rand() % 99 + 1;

            //only does this if based on rng and if there's any ships left
            if (shipSpawnRng > 50 && shipsLeft(ships))
            {
                //this picks a random ship from the list. the while loop runs until it picks a non 0 value
                
                //while (ships[randoShipsIndex] == 0)
                //{
                    randoShipsIndex = rand() % 3 + 1;
                    
                //}

                //creates a list that avaliableFunctions fills with all the directions the current ship can spawn in.
                //The current ship is whereever the loop is currently at, based on the row and colum index
                //Ships are spawned on one spot, then extended east, west, south, or north depending on their size
                
                avalDirections = checkAvaliableDirections(ships[randoShipsIndex],i,j);

                //calls the spawn check function to see if a ship has directions it can spawn that arent forbidden on this current spot,
                //as checked by the avalDirections above

                //similar randomization process to the randoShipIndex variable above, only for an index for the array of allowed directions
                randoSpawnDirectionIndex = rand() % 2 + 1;

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


//makes a board full of zeroes
void makeEmptyBoard()
{
    for(int i = 0; i < boardSize; i++)
    {
        for(int j = 0; j < boardSize; j++)
        {
        *(board + i * boardSize + j) = 0;
        }
    }
}


int main()
{
    //the player is asked for a board size, then the board is generated, given ships, and printed.
    
    std::cout << "How big do you want the board to be?\nEnter 1 number, boards will be square:";

    std::cin >> boardSize;

    std::cout << std::endl;
    
    board = create_2d_array();
    makeEmptyBoard();
    srand (time(NULL));

    shipGen();
    printBoard();

    return 0;
} 
// gcc battleship2.cpp -lstdc++