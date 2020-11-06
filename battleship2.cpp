#include <string>
#include <stdio.h>
#include <iostream>
#include <cstdlib>
#include <ctime>


int * board;
int boardSize = 0;
int moves = 0;

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

    //Checks South of current location
    int loopBeginPoint = currentRow + 1;
    int loopEndPoint = currentRow + 3;

    if (loopEndPoint > boardSize)
    {
        loopEndPoint = boardSize;
    }

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

     if (loopEndPoint < 0)
    {
        loopEndPoint = 0;
    }

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

     if (loopEndPoint > boardSize)
    {
        loopEndPoint = boardSize;
    }

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

     if (loopEndPoint < 0)
    {
        loopEndPoint = 0;
    }
    for (int j = loopBeginPoint; j >= loopEndPoint; j--)
    {
         if (*(board + currentRow * boardSize + j) == 1)
        {
            return false;
        }
    }
    return true;
}

//The master checker, responsible for running the spaceChecker based on the ship size,
//location and direction to spawn it's given
bool checker(int shipSize, int currentRow, int currentCol, char direction)
{

    //this int gives either the row or the col (set later, depending on the direction passed in)
    //of the last piece of the potential ship
    int lastPiece = 0;
    
    //this switch statement changes the way the space checker loop runs
    //based on the direction it's checking
    switch(direction)
    {
        case 'n':
        lastPiece = currentRow - shipSize; 

        //a similar if is checked in every direction, to make sure the last piece isnt
        //going to end up off the board
        if (lastPiece < 0)
        {
            return false;
        }

        for (int i = currentRow; i >= lastPiece;i--)
        {
            if (!spaceChecker(i, currentCol))
            {
                return false;
            }
        }
        break;

        case 's':
        lastPiece = currentRow + shipSize; 
        if (lastPiece > boardSize)
        {
            return false;
        }

        for (int i = currentRow; i <= lastPiece;i++)
        {
            if (!spaceChecker(i, currentCol))
            {
                return false;
            }
        }
        break;

        case 'e':
        lastPiece = currentCol + shipSize; 

        if (lastPiece > boardSize)
        {
            return false;
        }

        for (int j = currentCol; j <= lastPiece;j++)
        {
            if (!spaceChecker(currentRow, j))
            {
                return false;
            }
        }
        break;

        case 'w':
        lastPiece = currentCol - shipSize; 
        if (lastPiece < 0)
        {
            return false;
        }

        for (int j = currentCol; j >= lastPiece;j--)
        {
            if (!spaceChecker(currentRow, j))
            {
                return false;
            }
        }
        break;

        default:
        break;
    }
    return true;
}

//this calls checker() with each direction and updates the list of avaliable directions to spawn in accordingly
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

//spawns a ship based on the passed in direction, by going through a loop and changing the designated 0's
//on the board to 1's
void spawnShip(int currentRow, int currentCol, int shipToSpawn, char direction)
{
    //the row or col (depending on the direction the ship's spawning) of the last piece
    int lastPiece = 0;

    //this switch spawns the ship based on the direction its given
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

//loops through the entire board and determines whether or not it WILL or CAN spawn a ship there
void shipGen()
{
    //the list of avaliable directions a potential ship can spawn, updated later in the loop
    char * avalDirections = new char;

    //The 5 ships are: Carrier (occupies 5 spaces), Battleship (4), Cruiser (3), Submarine (3), and Destroyer (2)
    //This array helps me keep track of them, and make sure each is spawned just once
    int ships[5] = {5,4,3,3,2};

    //an rng that determines whether a ship will spawn at that spot
    int shipSpawnRng = 0;
    //indexes for getting random directions/ships, randomly generated and used later in loop
    int randoSpawnDirectionIndex = 0;
    int randoShipsIndex = 0;

    //the number of ships spawned, checked later in the loop to make sure no more than 5 are spawned
    int shipsSpawned = 0;

    //this loop checks every spot on the board
    for(int i = 0; i <= boardSize; i++)
    {
        for (int j  = 0; j <= boardSize; j++)
        {
            
            shipSpawnRng = rand() % 101;

            //where the ship spawning process begins, with a calculation to make one more likely to spawn
            //when 1 more is needed on the board
            if (shipSpawnRng > 50 - (shipsSpawned % 4))
            {
                //tindex of ship to spawn from the ships array above is randomly chosen
                randoShipsIndex = rand() % 5;
                
                //updates the list of avaliable directions to spawn in by running checkAvaliableDirections.
                avalDirections = checkAvaliableDirections(ships[randoShipsIndex],i,j);

                //a direction from the avaliable directions to spawn in is randomly chosen
                randoSpawnDirectionIndex = rand() % 4;
                    
                    //checks if there are < 5 ships on the board, if the random direction chosen is an actual direction and not an 'x',
                    //and if the random ship chosen isn't a 0
                    if (shipsSpawned < 5 && avalDirections[randoSpawnDirectionIndex] != 'x' && ships[randoShipsIndex] > 0)
                    {
                        //calls spawnShip() to spawn the ship at the current coordinates of the loop,
                        //sets the ship it just spawned to 0 in the ships array so it doesnt spawn againn'
                        //and increments the number of ships spawned
                        spawnShip(i, j, ships[randoShipsIndex], avalDirections[randoSpawnDirectionIndex]);
                        ships[randoShipsIndex] = 0;
                        shipsSpawned++;
                    }
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
////modified from: https://gist.github.com/kstatz12/1675e6823134f0c4437734148a9dcce3
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

//returns the value of the space passed in. called multiple times by fire()
int whatsHere(int row, int col)
{
    int here = *(board + row * boardSize + col);
    switch(here)
    {
        case 0:
        case 1:
            moves++;
            break;
        default:
        break;
    }
    return *(board + row * boardSize + col);
}

//checks the space passed in as well as the adjacent ones, and returns whether it was a hit, miss, or near miss
int fire(int row, int col)
{
    //For checking the adjacent spaces
    int northSpace = row-1;
    int southSpace = row+1;
    int eastSpace = col+1;
    int westSpace = col-1;

    bool nearMiss = false;

    //to be returned after the checks are done. 2 is a miss, 3 is a near miss, 4 is a hit, 5 means the space was previously checked
    int hitOrMiss = 0;

    if (whatsHere(northSpace,col)  == 1 || whatsHere(southSpace,col)  == 1 || whatsHere(row,eastSpace) == 1 || whatsHere(row,westSpace) == 1)
    {
        nearMiss = true;
    }

    hitOrMiss = *(board + row * boardSize + col);

    switch(hitOrMiss)
    {
        case 0:
            if (nearMiss)
            {
                hitOrMiss = 3;
            }
            else
            {
                hitOrMiss = 2;
            }
            break;

        case 1:
            hitOrMiss = 4;
            break;

        case 2:
        case 3:
        case 4:
            hitOrMiss = 5;
            break;

        default:
        break;
            
    }

    return hitOrMiss;
}

//Searches the entire board for ships. if there's a single '1' on the board, returns false
bool allDone()
{
    for(int i = 0; i < boardSize; i++)
    {
        for(int j = 0; j < boardSize; j++)
        {
          if (*(board + i * boardSize + j) == 1)
          {
              return false;
          }
        }
    }
    return true;
}

//called when a ship is found. goes in all four directions looking for the whole ship
void foundShip(int row, int col)
{
  //bool 
}


//used for checking spaces adjacent to another space. returns whether or not it's found the ship
bool nearMissChecker(int row, int col)
{
    bool found = false;
    int here = whatsHere(row, col);

    switch (here)
    {
        case 0:
            *(board + row * boardSize + col) = 2;
            break;
        case 1:
            *(board + row * boardSize + col) = 4;
            found = true;
            break;
        default:
        break;
    }

    return found;
}

//checks the area around a near miss for a ship, returns how many moves it took to find it
void nearMiss(int row, int col)
{
    bool foundIt = false;
    int northSpace = row-1;
    int southSpace = row+1;
    int eastSpace = col+1;
    int westSpace = col-1;

    //checks North, then proceeds to check the rest of the directions only if it hasnt found the ship yet
    foundIt = nearMissChecker(northSpace, col);

    if(!foundIt)
    {
        foundIt = nearMissChecker(southSpace, col);

        if(!foundIt)
        {
            foundIt = nearMissChecker(row, eastSpace);
            
            if(!foundIt)
            {
                foundIt = nearMissChecker(row, westSpace);
            }
        }
        
    }
}

//tries to hit every ship on the board in as few moves as possible. returns the moves it took
void boardSearch()
{
    
    bool done = false;

    int rowToCheck = 0;
    int colToCheck = 0;

    int fireResult = 0;

    //searches for the ships until it's done
    while (!done)
    {
        //selects a random row and col to fire upon
        rowToCheck = rand() % boardSize + 1;
        colToCheck = rand() % boardSize + 1;

        //fires, is returned what is found there
        fireResult = fire(rowToCheck, colToCheck);

        //unless that space has been already fired upon, increments moves and assigns that spot accordingly
        if(fireResult != 5)
        {
            *(board + rowToCheck * boardSize + colToCheck) = fireResult;

            switch (fireResult)
            {
                case 3:
                nearMiss(rowToCheck, colToCheck);
                break;

                case 4:
                foundShip(rowToCheck, colToCheck);
                break;

                default:
                break;

            }

        }
        done = allDone();
    }
}

int main()
{
    //the player is asked for a board size,
    
    std::cout << "How big do you want the board to be?\nEnter 1 number, boards will be square:";

    std::cin >> boardSize;
    
    //a 2darray is created, then filled with 0's
    board = create_2d_array();
    makeEmptyBoard();

    //ensures rng's are random each time, assigns a random seed based on the time
    srand (time(NULL));

    //ships are added, then the board is printed
    shipGen();
    printBoard();

    //only exists so the user can press enter to continue
    // char useless = 'd';

    // std::cout << "Press Enter to see how long\nit takes to find your ships!";

    // useless = std::cin.get();

    boardSearch();
    printBoard();

    std::cout <<"Found all Ships in "<<moves<<" moves.";

    free(board);
    return 0;
} 
// gcc battleship2.cpp -lstdc++