// EECS560_Lab1.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include "Min3Heap.h"

int getChoice();
void menuLoop( Min3Heap& min3Heap );
void insertItem( Min3Heap& min3Heap );
void deleteItem( Min3Heap& min3Heap );
void deletemin( Min3Heap& min3Heap );
void deletemax( Min3Heap& min3Heap );
void printLevelOrder( Min3Heap& min3Heap );

int main()
{
    int anInteger;
    std::ifstream fileReader( "data.txt" );

    if( fileReader.is_open() )
    {
        Queue<int> readValues;

        while( fileReader >> anInteger )
        {
            readValues.enqueue( anInteger );
        }

        Min3Heap min3Heap( 200, readValues );

        menuLoop( min3Heap );
        fileReader.close();
    }
    else
    {
        std::cout << "Error reading file\n";
    }

    return 0;
}

void menuLoop( Min3Heap& min3Heap )
{
    int choice = 0;

    while( choice != 6 )
    {
        choice = getChoice();

        switch( choice )
        {
        case 1:
            insertItem( min3Heap );
            break;
        case 2:
            deletemin( min3Heap );
            break;
        case 3:
            deletemax( min3Heap );
            break;
        case 4:
            deleteItem( min3Heap );
            break;
        case 5:
            printLevelOrder( min3Heap );
            break;
        default:
            if( choice != 6 )
            {
                std::cout << "Enter a valid choice (1-5)\n";
            }
            break;
        }
    }
}

int getChoice()
{
    int choice = 0;

    std::cout << "..........................................................\n";
    std::cout << "Please choose one of the folowing commands:\n";
    std::cout << "1 - insert\n"
        << "2 - deletemin\n"
        << "3 - deletemax\n"
        << "4 - remove\n"
        << "5 - levelorder\n"
        << "6 - exit\n"
        << "\n";

    std::cin >> choice;

    return choice;
}

void insertItem( Min3Heap& min3Heap )
{
    std::cout << "Choose a number to be added to the heap\n";
    int number;
    std::cin >> number;
    min3Heap.insert( number );
}

void deleteItem( Min3Heap& min3Heap )
{
    std::cout << "Choose a number to be removed from the heap\n";
    int number;
    std::cin >> number;
    if( !min3Heap.remove( number ) )
    {
        std::cout << "Error, cannot delete " << number << ", value is not in the heap.\n";
    }
}

void deletemin( Min3Heap& min3Heap )
{
    if( min3Heap.deleteMin() == -1 )
    {
        std::cout << "The heap is empty\n";
    }
}

void deletemax( Min3Heap& min3Heap )
{
    if( min3Heap.deleteMax() == -1)
    {
        std::cout << "The heap is empty\n";
    }
}

void printLevelOrder( Min3Heap& min3Heap )
{
    std::cout << "Level Order:\n";
    min3Heap.levelOrderDisplay();
    std::cout << std::endl;
}

//int main()
//{
//    int nValues[] = { 50000, 100000, 200000, 400000 };
//
//    for ( int i = 0; i < 4; i++ )
//    {
//
//    }
//    return 0;
//}