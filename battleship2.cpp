#include <string>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <time.h>;


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

    //THE BELOW VARIABLES ARE PARAMETERS FOR THE FOR LOOPS

    //These project where the coordinates of the last piece of the ship will be if it's allowed to spawn, calculated below
    //based on ship size, the coordinates of the bottom piece of the ship, and the direction it'll face.
    int lastRowShipTouches = 0;
    int lastColShipTouches = 0;
    


    //These are variable for special checks that are only done at the first and last pieces of the ship
    //It's only necessary for the front and back pieces of the ship to check 3 spaces in their aligntment (horizontal or vertical)
    //(for example; a WEST facing ship would need to check 3 spaces EAST of the first piece of the ship, and 3 WEST of the last piece)
    //The non-bordering pieces of the ship check 3 spaces horizontally (if the ship is vertical) or vertically (if ship is horizontal)
    
    //TO WHOEVER READS THIS, I REALLY HOPED I EXPLAINED THAT WELL.

    int threeSpacesVerticalOfTheFirstPiece = 0;
    int threeSpacesHorizontalOfTheFirstPiece = 0;

    int threeSpacesVerticalOfTheLastPiece = 0;
    int threeSpacesHorizontalOfTheLastPiece = 0;
    
    //this switch statement changes the values above based on which direction the ship will spawn in.
    switch(direction)
    {
        case 'n':
        lastRowShipTouches = currentRow + shipSize - 1;
        threeSpacesVerticalOfTheFirstPiece = currentRow + 3;
        threeSpacesVerticalOfTheLastPiece = lastRowShipTouches + 3;
        break;

        case 's':
        lastRowShipTouches =  currentRow + shipSize + 1;
        threeSpacesVerticalOfTheFirstPiece = currentRow - 3;
        threeSpacesVerticalOfTheLastPiece = lastRowShipTouches - 3;
        break;

        case 'e':
        lastColShipTouches = currentCol  + shipSize -1;
        threeSpacesHorizontalOfTheFirstPiece = currentCol - 3;
        threeSpacesHorizontalOfTheLastPiece = lastColShipTouches + 3;
        break;

        case 'w':
        lastColShipTouches = currentCol - shipSize + 1;
        threeSpacesHorizontalOfTheFirstPiece = currentCol + 3;
        threeSpacesHorizontalOfTheLastPiece = lastColShipTouches - 3;
        break;

        default:
        break;
    }

    //if the end piece of the ship will be out of bounds, the ship cannot spawn
    if (lastRowShipTouches > boardSize || lastRowShipTouches < 0 || lastColShipTouches > boardSize || lastColShipTouches < 0)
    {
        canSpawn = false;
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
    int rowOfFinalPiece = 0;
    int colOfFinalPiece = 0;

    //these decide whether the loop will increment north or south, and east or south of the board
    //whien spawning the ship. 
    int northOrSouth = 0;
    int eastOrWest = 0;

    //These are ints will be conditions for stopping the ship spawn loop.
    //Because I cant just use a simple greater/less than operator, this is how I'm doin it.
    //The spawn horizontal and vertical spawn loops will stop when they ARE EQUAL to these ints
    int stopRowLoopHere = 0;
    int stopColLoopHere = 0;

    switch (direction)
    {
        case 'n':
            rowOfFinalPiece = currentRow - shipToSpawn + 1;
            colOfFinalPiece = currentCol;

            northOrSouth = -1;
            eastOrWest = 1;

            stopRowLoopHere = rowOfFinalPiece - 1;
            stopColLoopHere = currentCol + 1;
        break;

        case 's':
            rowOfFinalPiece = currentRow + shipToSpawn - 1;
            colOfFinalPiece = currentCol;

            northOrSouth = 1;
            eastOrWest = 1;

            stopRowLoopHere = rowOfFinalPiece + 1;
            stopColLoopHere = currentCol + 1;
        break;

        case 'e':
            northOrSouth = 1;
            eastOrWest = 1;

            stopRowLoopHere = rowOfFinalPiece + 1;
            stopColLoopHere = colOfFinalPiece + 1;
        break;

        case 'w':
            northOrSouth = 1;
            eastOrWest = -1;

            stopRowLoopHere = rowOfFinalPiece + 1;
            stopColLoopHere = colOfFinalPiece - 1;
        break;

        default:
        break;
    }

      for(int i = currentRow; i != rowOfFinalPiece; i += northOrSouth)
    {
        for(int j = currentCol; j != colOfFinalPiece; j += eastOrWest)
        {
            *(board + i * boardSize + currentCol) = 1;
        }
    }
  }

//big method for putting every ship on the board
void shipGen()
{
    char * avalDirections = new char;
    //The 5 ships are: Carrier (occupies 5 spaces), Battleship (4), Cruiser (3), Submarine (3), and Destroyer (2).
    int ships[5] = {5,4,3,3,2};
    int shipSpawnRng = 52;
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

                    spawnShip(i, j, 1, avalDirections[randoSpawnDirectionIndex]);
                    ships[randoShipsIndex] = 0;
            }
            
        }
    }
}


//modified from: https://gist.github.com/kstatz12/1675e6823134f0c4437734148a9dcce3
void printBoard()
{
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
    
    shipGen();
    printBoard();

    return 0;
} 
// gcc battleship2.cpp -lstdc++