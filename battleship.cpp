#include <string>
#include <stdio.h>
#include <iostream>
#include <cstdlib>



int * create_2d_array(const int rows, const int cols)
{
     std::cout << "create2darray";
    return (int*)malloc(rows * cols *sizeof(int));
}

int * fill(int * array, const int rows, const int cols)
{
    for(int i = 0; i < rows; i++)
    {
        for (int j  = 0; j < cols; j++)
        {
            *(array + i * cols + j) = i;
        }
    }
}

int * fillEmpty(int * array, const int rows, const int cols)
{
    for(int i = 0; i < rows; i++)
    {
        for (int j  = 0; j < cols; j++)
        {
            *(array + i * cols + j) = 0;
        }
    }
     std::cout << "fillempty";

}

void printBoard(int * array, const int rows,  const int cols)
{
    for(int i = 0; i < rows; i++)
    {
        for(int j = 0; j < rows; j++)
        {
           std::cout << *(array + i * cols + j) <<"";
        }
        std::cout << std::endl;
    }
     std::cout << "printboard";
}

int * boardGen(int size)
{
    std::cout << "BoardGen";
    int * board = create_2d_array(size, size);
    board = fillEmpty(board, size, size);


    return board;
}

int main()
{
    int boardSize = 0;

    std::cout << "How big do you want the board to be?\nEnter 1 number, boards will have equal width/length:";
    std::cout << std::endl;
    
    std::cin >> boardSize;
    

    int * board = boardGen(boardSize);
    printBoard(board, boardSize, boardSize);

    return 1;
} 

//gcc battleship.cpp -lstdc++