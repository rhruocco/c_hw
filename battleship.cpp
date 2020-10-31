#include <string>
#include <stdio.h>
#include <iostream>
#include <cstdlib>

int * create_2d_array(const int rows, const int cols)
{
    return (int*)malloc(rows * cols *sizeof(int));
}

//the check(direction) methods all have the same template
//they check to see if a ship can be spawned facing that direction
bool checkEast(int * board, const int rows, const int cols, int shipSize, int currentRow, int currentCol)
{
    //this int is the end of the ship, the offset at the end is cause the loops below start at the currentposition on the board
  int lastColShipTouches = currentCol + shipSize - 1;

  if (lastColShipTouches > cols)
  {
      //checks to see if the last ship would be outside the board, returns false
      return false;
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
              if (*(board + currentRow * cols + left) == 1)
              {
                  return false;
              }
          }
       }

       //same as the if above, but instead it checks 3 ahead of the last part of the ship
       else if (j == lastColShipTouches && currentCol < cols)
       {
          for (int right = j + 1; right <= (j + 3); right++)
          {
              if (*(board + currentRow * cols + right) == 1)
              {
                  return false;
              }
          }
       }

       //all the other parts of the ship use this check, to check (in this case) up and down
       else
       {
           for (int down = currentRow + 1; down <= (currentRow+ 3); down++)
           {
               if (*(board + down * cols + j) == 1)
               {
                   return false;
               }
           }
           for (int up = currentRow - 1; up >= (currentRow - 3); up--)
           {
               if (*(board + up * cols + j) == 1)
               {
                   return false;
               }
           }
       }
       
   }
}


//edit of checkEast
bool checkWest(int * board, const int rows, const int cols, int shipSize, int currentRow, int currentCol)
{
  int lastColShipTouches = currentCol - shipSize + 1;
  if (lastColShipTouches < 0)
  {
      return false;
  }

   for (int j = currentCol; j >= lastColShipTouches ; j--)
   {
       if (j == lastColShipTouches && currentCol < 0)
       {
          for (int left = j - 1; left >= (j - 3); left--)
          {
              std::cout << "hi";
              if (*(board + currentRow * cols + left) == 1)
              {
                  return false;
              }
          }
       }
       else if (j == currentCol && currentCol > cols)
       {
          for (int right = j + 1; right <= (j + 3); right++)
          {
              if (*(board + currentRow * cols + right) == 1)
              {
                  return false;
              }
          }
       }
       else
       {
           for (int down = currentRow + 1; down <= (currentRow+ 3); down++)
           {
               if (*(board + down * cols + j) == 1)
               {
                   return false;
               }
           }
           for (int up = currentRow - 1; up >= (currentRow - 3); up--)
           {
               if (*(board + up * cols + j) == 1)
               {
                   return false;
               }
           }
       }
       
   }
}

//edit of checkEast
bool checkSouth(int * board, const int rows, const int cols, int shipSize, int currentRow, int currentCol)
{
    int lastRowShipTouches = currentRow + shipSize - 1;

    if (lastRowShipTouches > rows)
  {
      return false;
  }

   for (int i = currentRow; i <= lastRowShipTouches; i++)
   {
       if (i == currentRow && currentRow < rows)
       {
          std::cout << "in if\n";
          for (int up = (i - 1); up >= (i - 3); up--)
          {
              std::cout << "im in the else if for loop";
              if (*(board + up * cols + currentCol) == 1)
              {
                  return false;
              }
          }
       }
       else if (i == lastRowShipTouches && currentRow > 0)
       {
          for (int down = i + 1; down <= (i + 3); down++)
          {
              if (*(board + down * cols + currentCol) == 1)
              {
                  return false;
              }
          }
       }
       
       else
       {
           std::cout << "in else\n";
           for (int right = currentCol + 1; right <= (currentCol+ 3); right++)
           {
               if (*(board + i * cols + right) == 1)
               {
                   return false;
               }
           }
           for (int left = currentCol - 1; left >= (currentCol - 3); left--)
           {
               if (*(board + i * cols + left) == 1)
               {
                   return false;
               }
           }
       }    
   }
}

//edit of checkEast
bool checkNorth(int * board, const int rows, const int cols, int shipSize, int currentRow, int currentCol)
{
    int lastRowShipTouches = currentRow + shipSize - 1;
   
     if (lastRowShipTouches > rows)
  {
      return false;
  }

   for (int i = currentRow; i <= lastRowShipTouches ; i++)
   {
       if (i == currentRow && currentRow < rows)
       {
          for (int down = i - 1; down <= (i - 3); down--)
          {
              if (*(board + down * cols + currentCol) == 1)
              {
                  return false;
              }
          }
       }
       else if (i == lastRowShipTouches && currentRow > 0)
       {
          for (int up = i + 1; up >= (i + 3); up++)
          {
              if (*(board + up * cols + currentCol) == 1)
              {
                  return false;
              }
          }
       }
       else
       {
           for (int right = currentCol + 1; right <= (currentCol+ 3); right++)
           {
               if (*(board + i * cols + right) == 1)
               {
                   return false;
               }
           }
           for (int left = currentCol - 1; left >= (currentCol - 3); left--)
           {
               if (*(board + i * cols + left) == 1)
               {
                   return false;
               }
           }
       }
       
   }
}

//this calls each direction's check to see which directions a ship can spawn in given its coordinates
char * avaliableDirections(int * board, const int rows, const int cols, int shipSize, int currentRow, int currentCol)
{
    //a list of all the directions
    char directions [4] = {'n','s','e','w'};
    if (!checkNorth(board, rows, cols, shipSize, currentRow, currentCol))
    {
        directions[0] = 'x';
    }
    if (!checkSouth(board, rows, cols, shipSize, currentRow, currentCol))
    {
        directions[1] = 'x';
    }
    if (!checkEast(board, rows, cols, shipSize, currentRow, currentCol))
    {
        directions[2] = 'x';
    }
    if (!checkWest(board, rows, cols, shipSize, currentRow, currentCol))
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
int * spawnShip(int * board, const int rows, const int cols, int currentRow, int currentCol, int shipToSpawn, char direction)
{
    int stopHere = 0;
  if (direction == 'n')
  {
      stopHere = currentRow - shipToSpawn + 1;
      for(int i = currentRow; i > stopHere; i--)
    {
        *(board + i * cols + currentCol) = 1;
    }
  }
  else if (direction == 's')
  {
      stopHere = currentRow + shipToSpawn - 1;
      for(int i = currentRow; i < stopHere; i++)
    {
        *(board + i * cols + currentCol) = 1;
    }
  }
  else if (direction == 'e')
  {
      stopHere = currentCol + shipToSpawn - 1;
      for(int j = currentRow; j < stopHere; j++)
    {
        *(board + currentRow * cols + j) = 1;
    }
  }
  else if (direction == 'w')
  {
      stopHere = currentCol - shipToSpawn + 1;
      for(int j = currentCol; j > stopHere; j--)
    {
        *(board + currentRow * cols + j) = 1;
    }
  }
  //returns modified board
  return board;
}

//big method for putting every ship on the board
int * shipGen(int * array, const int rows, const int cols)
{
    //The 5 ships are: Carrier (occupies 5 spaces), Battleship (4), Cruiser (3), Submarine (3), and Destroyer (2).
    int ships[5] = {5,4,3,3,2};

    //this loop checks every spot on the board
    for(int i = 0; i < rows; i++)
    {
        for (int j  = 0; j < cols; j++)
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
                
                char * avalDirections = avaliableDirections(array,rows,cols,ships[randoShipsIndex],i,j);

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

                    array = spawnShip(array,rows, cols, i, j, ships[randoShipsIndex], avalDirections[randoSpawnDirectionIndex]);
                    ships[randoShipsIndex] = 0;
                }
            }
            
        }
    }
    //returns finished board with ships
    return array;
}

void printBoard(int * array, const int rows,  const int cols)
{
    //iterates thru the board and prints each space
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < rows; j++)
        {
           std::cout << *(array + i * cols + j) <<" ";
        }
        std::cout << std::endl;
    }
     std::cout << "Let's Play Battlship!\n";
}

int * boardGen(int size)
{
    //calls the 2darray function, returns its result
    int * board = create_2d_array(size, size);

    return board;
}

int main()
{
    //the player is asked for a board size, then the board is generated, given ships, and printed.
    int boardSize = 0;

    std::cout << "How big do you want the board to be?\nEnter 1 number, boards will be square:";
    
    std::cin >> boardSize;

    int * board = boardGen(boardSize);
    board = shipGen(board,boardSize,boardSize);
    printBoard(board, boardSize, boardSize);

    return 0;
} 
// gcc battleship.cpp -lstdc++