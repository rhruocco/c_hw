#include <string>
#include <stdio.h>
#include <iostream>
#include <cstdlib>

int * create_2d_array(const int rows, const int cols)
{
    return (int*)malloc(rows * cols *sizeof(int));
}

char * avaliableDirections(int * board, const int rows, const int cols, int shipSize, int currentRow, int currentCol)
{
    char directions [4] = {'n','s','e','w'};



    return avalDirections;
}


bool checkEast(int * board, const int rows, const int cols, int shipSize, int currentRow, int currentCol)
{
  for (int i)
}

//GOING NORTH MEANS DECREASING I
bool checkNorth(int * board, const int rows, const int cols, int shipSize, int currentRow, int currentCol)
{
   int spaceNeeded = (3 + shipSize) * -1;
   

   for (int i = currentRow; i <= spaceNeeded; i++)
   {

   }
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

// int shipSize(int * ships)
// {

// }

int * shipGen(int * array, const int rows, const int cols)
{
    //The 5 ships are: Carrier (occupies 5 spaces), Battleship (4), Cruiser (3), Submarine (3), and Destroyer (2).

    // int shipsToAdd = 5;
    // int threeShips = 0; //this counts how many ships that are 3 spaces big are currently on the board, there should be 2 at the end
    // bool spawnedBattleship = false, spawnedCarrier = false, spawnedDestroyer = false; //Keeps track of if all the other ships have spawned

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
        //std::cout << "Row" <<i <<"\n";
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

    std::cout << "How big do you want the board to be?\nEnter 1 number, boards will have equal width/length:";
    
    std::cin >> boardSize;

    int * board = boardGen(boardSize);
    printBoard(board, boardSize, boardSize);

    return 0;
} 
// gcc battleship.cpp -lstdc++