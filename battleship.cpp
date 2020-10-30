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
  int lastColShipTouches = currentCol + shipsize - 1;

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
  int lastColShipTouches = currentCol - shipsize + 1;

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
       else if (j == currentCol && currentCol > col)
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
   int lastRowShipTouches = currentRow + shipsize - 1;

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
   int lastRowShipTouches = currentRow - shipsize + 1;

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
    char directions [4] = {'n','s','e','w'};
    if (!checkNorth(int * board, const int rows, const int cols, int shipSize, int currentRow, int currentCol))
    {
        directions[0] = 'x';
    }
    if (!checkSouth(int * board, const int rows, const int cols, int shipSize, int currentRow, int currentCol))
    {
        directions[1] = 'x';
    }
    if (!checkEast(int * board, const int rows, const int cols, int shipSize, int currentRow, int currentCol))
    {
        directions[2] = 'x';
    }
    if (!checkWest(int * board, const int rows, const int cols, int shipSize, int currentRow, int currentCol))
    {
        directions[3] = 'x';
    }
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

int * shipGen(int * array, const int rows, const int cols)
{
    //The 5 ships are: Carrier (occupies 5 spaces), Battleship (4), Cruiser (3), Submarine (3), and Destroyer (2).

    int ships [5] = {5,4,3,3,2};

    for(int i = 0; i < rows; i++)
    {
        for (int j  = 0; j < cols; j++)
        {
            //random ship gen
            if ((rand() % 100) > 50 && shipsLeft(ships))
            {
                int randoShipsIndex = rand % 4;
                while (ships[randoShipsIndex] == 0)
                {
                    randoShipsIndex = rand % 4;
                }

                if (shipCheck(array, rows, cols, ships[]))
                
              *(array + i * cols + j) = 1;
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