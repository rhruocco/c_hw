#include <string>
#include <stdio.h>
#include <iostream>
#include <cstdlib>

int * create_2d_array(const int rows, const int cols)
{
    return (int*)malloc(rows * cols *sizeof(int));
}

//Going east means increasing columns (j)
bool checkEast(int * board, const int rows, const int cols, int shipSize, int currentRow, int currentCol)
{
    std::cout << "gagagaShipFUCKs...\n";
  int lastColShipTouches = currentCol + shipSize - 1;
  if (lastColShipTouches > cols)
  {
      return false;
  }

   for (int j = currentCol; j <= lastColShipTouches ; j++)
   {
       if (j == currentCol && currentCol > 0)
       {
          for (int left = j - 1; left >= (j - 3); left--)
          {
              if (*(board + currentRow * cols + left) == 1)
              {
                  return false;
              }
          }
       }
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

bool checkWest(int * board, const int rows, const int cols, int shipSize, int currentRow, int currentCol)
{
    std::cout << "65656gagagaShips...\n";
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

bool checkSouth(int * board, const int rows, const int cols, int shipSize, int currentRow, int currentCol)
{
    std::cout << "gagsada1111agaShips...\n";
    int lastRowShipTouches = currentRow + shipSize - 1;
    if (lastRowShipTouches > rows)
  {
      return false;
  }

   for (int i = currentRow; i <= lastRowShipTouches ; i++)
   {
       if (i == lastRowShipTouches && currentRow > 0)
       {
          for (int down = i + 1; down <= (i + 3); down++)
          {
              if (*(board + down * cols + currentCol) == 1)
              {
                  return false;
              }
          }
       }
       else if (i == currentRow && currentRow < rows)
       {
          for (int up = i - 1; up >= (i - 3); up--)
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

//GOING NORTH MEANS DECREASING ROWS {i}
bool checkNorth(int * board, const int rows, const int cols, int shipSize, int currentRow, int currentCol)
{
    std::cout << "gagagaShips...\n";
   int lastRowShipTouches = currentRow - shipSize + 1;
     if (lastRowShipTouches < 0)
  {
      return false;
  }

   for (int i = currentRow; i >= lastRowShipTouches ; i--)
   {
       if (i == currentRow && currentRow < rows)
       {
          for (int down = i + 1; down <= (i + 3); down++)
          {
              if (*(board + down * cols + currentCol) == 1)
              {
                  return false;
              }
          }
       }
       else if (i == lastRowShipTouches && currentRow > 0)
       {
          for (int up = i - 1; up >= (i - 3); up--)
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

char * avaliableDirections(int * board, const int rows, const int cols, int shipSize, int currentRow, int currentCol)
{
    std::cout << "Adsadasdewwww1211 Ships...\n";
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
    std::cout << "Adding Ships...\n";
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

bool canThisShipSpawn(char * drections)
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
  return board;
}

int * shipGen(int * array, const int rows, const int cols)
{
    //The 5 ships are: Carrier (occupies 5 spaces), Battleship (4), Cruiser (3), Submarine (3), and Destroyer (2).
    std::cout << "Ass...\n";
    int ships [5] = {5,4,3,3,2};

    for(int i = 0; i < rows; i++)
    {
        for (int j  = 0; j < cols; j++)
        {
            //random ship gen
            if ((rand() % 100) > 50 && shipsLeft(ships))
            {
                std::cout << "Ass Ships...\n";
                int randoShipsIndex = rand() % 4;
                while (ships[randoShipsIndex] == 0)
                {
                    randoShipsIndex = rand() % 4;
                    std::cout << "Assssss Ships...\n";
                }
                std::cout << "Asss Ships...\n";

                char * avalDirections = avaliableDirections(array,rows,cols,ships[randoShipsIndex],i,j);
                std::cout << "Assasdas Ships...\n";

                if (canThisShipSpawn(avalDirections))
                {
                    int randoSpawnDirectionIndex = rand() % 3;
                    while (avalDirections[randoSpawnDirectionIndex] == 'x')
                    {
                        randoSpawnDirectionIndex = rand() % 3;
                    }

                    array = spawnShip(array,rows, cols, i, j, ships[randoShipsIndex], avalDirections[randoSpawnDirectionIndex]);
                }
            }
            
        }
    }
    std::cout << "Adding Ships...\n";
    return array;
}

void printBoard(int * array, const int rows,  const int cols)
{
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
    std::cout << "BoardGen\n";
    int * board = create_2d_array(size, size);
    board = shipGen(board,size,size);

    return board;
}

int main()
{
    int boardSize = 0;

    std::cout << "How big do you want the board to be?\nEnter 1 number, boards will be square:";
    
    std::cin >> boardSize;

    int * board = boardGen(boardSize);
    printBoard(board, boardSize, boardSize);

    return 0;
} 
// gcc battleship.cpp -lstdc++