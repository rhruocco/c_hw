#include <string>
#include <stdio.h>
#include <iostream>
#include <cstdlib>


int * board;
int boardSize = 0;

//Taken from: https://gist.github.com/kstatz12/1675e6823134f0c4437734148a9dcce3
int * create_2d_array()
{
    return (int*)malloc(boardSize * boardSize *sizeof(int));
}



//the check(direction) methods all have the same template
//they check to see if a ship can be spawned facing that direction
bool checkEast(int shipSize, int currentRow, int currentCol)
{
  bool canSpawn = true;
    //this int is the end of the ship, the offset at the end is cause the loops below start at the currentposition on the board
  int lastColShipTouches = currentCol + shipSize - 1;

  if (lastColShipTouches > boardSize)
  {
      //checks to see if the last ship would be outside the board, returns false
      canSpawn = false;
  }

//this is the big loop that checks the current spot on the board's surroundings
   for (int j = currentCol; j <= lastColShipTouches ; j++)
   {
       //this only runs if it's the first part of the ship. it checks 3 in the opposite direction
       if (j == currentCol && currentCol > 0)
       {
          for (int left = j - 1; left >= (j - 3); left--)
          {
              std::cout << "in for";
              if (*(board + currentRow * boardSize + left) == 1)
              {
                  canSpawn = false;
              }
          }
       }

       //same as the if above, but instead it checks 3 ahead of the last part of the ship
       else if (j == lastColShipTouches && currentCol < boardSize)
       {
          for (int right = j + 1; right <= (j + 3); right++)
          {
              if (*(board + currentRow * boardSize + right) == 1)
              {
                  canSpawn = false;
              }
          }
       }

       //all the other parts of the ship use this check, to check (in this case) up and down
       else
       {
           for (int down = currentRow + 1; down <= (currentRow+ 3); down++)
           {
               if (*(board + down * boardSize + j) == 1)
               {
                   canSpawn = false;
               }
           }
           for (int up = currentRow - 1; up >= (currentRow - 3); up--)
           {
               if (*(board + up * boardSize + j) == 1)
               {
                   canSpawn = false;
               }
           }
       }
       
   }
   return canSpawn;
}


//edit of checkEast
bool checkWest(int shipSize, int currentRow, int currentCol)
{
    bool canSpawn = true;
  int lastColShipTouches = currentCol - shipSize + 1;
  if (lastColShipTouches < 0)
  {
      canSpawn = false;
  }

   for (int j = currentCol; j >= lastColShipTouches ; j--)
   {
       if (j == lastColShipTouches && currentCol < 0)
       {
          for (int left = j - 1; left >= (j - 3); left--)
          {
              std::cout << "hi";
              if (*(board + currentRow * boardSize + left) == 1)
              {
                  canSpawn = false;
              }
          }
       }
       else if (j == currentCol && currentCol > boardSize)
       {
          for (int right = j + 1; right <= (j + 3); right++)
          {
              if (*(board + currentRow * boardSize + right) == 1)
              {
                  canSpawn = false;
              }
          }
       }
       else
       {
           for (int down = currentRow + 1; down <= (currentRow+ 3); down++)
           {
               if (*(board + down * boardSize + j) == 1)
               {
                   canSpawn = false;
               }
           }
           for (int up = currentRow - 1; up >= (currentRow - 3); up--)
           {
               if (*(board + up * boardSize + j) == 1)
               {
                   canSpawn = false;
               }
           }
       }
       
   }
   return canSpawn;
}

//edit of checkEast
bool checkSouth(int shipSize, int currentRow, int currentCol)
{
    bool canSpawn = true;
    int lastRowShipTouches = currentRow + shipSize - 1;

    if (lastRowShipTouches > boardSize)
  {
      canSpawn = false;
  }

   for (int i = currentRow; i <= lastRowShipTouches; i++)
   {
       if (i == currentRow && currentRow < boardSize)
       {
          std::cout << "in if\n";
          for (int up = (i - 1); up >= (i - 3); up--)
          {
              std::cout << "im in the else if for loop";
              if (*(board + up * boardSize + currentCol) == 1)
              {
                  canSpawn = false;
              }
          }
       }
       else if (i == lastRowShipTouches && currentRow > 0)
       {
          for (int down = i + 1; down <= (i + 3); down++)
          {
              if (*(board + down * boardSize + currentCol) == 1)
              {
                  canSpawn = false;
              }
          }
       }
       
       else
       {
           std::cout << "in else\n";
           for (int right = currentCol + 1; right <= (currentCol+ 3); right++)
           {
               if (*(board + i * boardSize + right) == 1)
               {
                   canSpawn = false;
               }
           }
           for (int left = currentCol - 1; left >= (currentCol - 3); left--)
           {
               if (*(board + i * boardSize + left) == 1)
               {
                   canSpawn = false;
               }
           }
       }    
   }
   return canSpawn;
}


//The further south, the greater the row value
//The further east, the greater the column value
bool checker(int shipSize, int currentRow, int currentCol)
{
    bool canSpawn = true;
    int lastRowShipWillTouch = 0;
    int lastColShipWillTouch = 0;
}

//edit of checkEast
bool checkNorth(int shipSize, int currentRow, int currentCol)
{
    bool canSpawn = true;
    int lastRowShipTouches = currentRow + shipSize - 1;
   
     if (lastRowShipTouches > boardSize)
  {
      canSpawn = false;
  }

   for (int i = currentRow; i <= lastRowShipTouches ; i++)
   {
       if (i == currentRow && currentRow < boardSize)
       {
          for (int down = i - 1; down <= (i - 3); down--)
          {
              if (*(board + down * boardSize + currentCol) == 1)
              {
                  canSpawn = false;
              }
          }
       }
       else if (i == lastRowShipTouches && currentRow > 0)
       {
          for (int up = i + 1; up >= (i + 3); up++)
          {
              if (*(board + up * boardSize + currentCol) == 1)
              {
                  canSpawn = false;
              }
          }
       }
       else
       {
           for (int right = currentCol + 1; right <= (currentCol+ 3); right++)
           {
               if (*(board + i * boardSize + right) == 1)
               {
                   canSpawn = false;
               }
           }
           for (int left = currentCol - 1; left >= (currentCol - 3); left--)
           {
               if (*(board + i * boardSize + left) == 1)
               {
                   canSpawn = false;
               }
           }
       }
       
   }
   return canSpawn;
}

//this calls each direction's check to see which directions a ship can spawn in given its coordinates
char * avaliableDirections(int shipSize, int currentRow, int currentCol)
{
    //a list of all the directions
    char directions [4] = {'n','s','e','w'};
    if (!checkNorth(shipSize, currentRow, currentCol))
    {
        directions[0] = 'x';
    }
    if (!checkSouth(shipSize, currentRow, currentCol))
    {
        directions[1] = 'x';
    }
    if (!checkEast(shipSize, currentRow, currentCol))
    {
        directions[2] = 'x';
    }
    if (!checkWest(shipSize, currentRow, currentCol))
    {
        directions[3] = 'x';
    }

    //replacing a direction with an x means that it cant spawn a ship in that direction. it returns the modified directions list
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

bool canThisShipSpawn(char * drections) //checks to see if a ship spawn. it does this by simply checking if all the values of the array passed
//in are 'x''s. if so, returns false
{
    bool anyDirections = false;
    for(int i = 0; i < 3; i++)
    {
        if (drections[i] != 'x')
        {
            anyDirections = true;
        }
    }
    return anyDirections;
}

//spawns a ship based on the passed in direction, by going through a loop and changing the 0's to 1's
void spawnShip(int currentRow, int currentCol, int shipToSpawn, char direction)
{
    int stopHere = 0;
  if (direction == 'n')
  {
      stopHere = currentRow - shipToSpawn + 1;
      for(int i = currentRow; i > stopHere; i--)
    {
        *(board + i * boardSize + currentCol) = 1;
    }
  }
  else if (direction == 's')
  {
      stopHere = currentRow + shipToSpawn - 1;
      for(int i = currentRow; i < stopHere; i++)
    {
        *(board + i * boardSize + currentCol) = 1;
    }
  }
  else if (direction == 'e')
  {
      stopHere = currentCol + shipToSpawn - 1;
      for(int j = currentRow; j < stopHere; j++)
    {
        *(board + currentRow * boardSize + j) = 1;
    }
  }
  else if (direction == 'w')
  {
      stopHere = currentCol - shipToSpawn + 1;
      for(int j = currentCol; j > stopHere; j--)
    {
        *(board + currentRow * boardSize + j) = 1;
    }
  }
}

//big method for putting every ship on the board
void shipGen()
{
    //The 5 ships are: Carrier (occupies 5 spaces), Battleship (4), Cruiser (3), Submarine (3), and Destroyer (2).
    int ships[5] = {5,4,3,3,2};

    //this loop checks every spot on the board
    for(int i = 0; i < boardSize; i++)
    {
        for (int j  = 0; j < boardSize; j++)
        {
            //only continues based on rng and if there's any ships left
            if ((rand() % 100) > 50 && shipsLeft(ships))
            {
                //this picks a random ship from the list. the while loop runs until it picks a non 0 value
                int randoShipsIndex = rand() % 4;
                while (ships[randoShipsIndex] == 0)
                {
                    randoShipsIndex = rand() % 4;
                }

                //creates a list that avaliableFunctions fills with all the directions the current ship can spawn in.
                //The current ship is whereever the loop is currently at, based on the row and colum index
                //Ships are spawned on one spot, then extended east, west, south, or north depending on their size
                
                char * avalDirections = avaliableDirections(ships[randoShipsIndex],i,j);

                //calls the spawn check function to see if a ship has directions it can spawn that arent forbidden on this current spot,
                //as checked by the avalDirections above
                if (canThisShipSpawn(avalDirections))
                {

                    //similar randomization process to the randoShipIndex variable above, only for an index for the array of allowed directions
                    int randoSpawnDirectionIndex = rand() % 3;
                    while (avalDirections[randoSpawnDirectionIndex] == 'x')
                    {
                        randoSpawnDirectionIndex = rand() % 3;
                    }

                    //calls the spawnShip function to begin the spawning process at wherever the loop is at. (represented by i for row and j for col)
                    //then, that ship is given a value of 0 in the ships array so it doesnt get spawned again

                    spawnShip(i, j, ships[randoShipsIndex], avalDirections[randoSpawnDirectionIndex]);
                    ships[randoShipsIndex] = 0;
                }
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
    
    board = create_2d_array();
    
    shipGen();
    printBoard();

    return 0;
} 
// gcc battleship2.cpp -lstdc++