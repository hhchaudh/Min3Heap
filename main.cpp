//// EECS560_Lab1.cpp : Defines the entry polong for the console application.
////
//
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "Min3Heap.h"
#include "BinarySearchTree.h"
//
//long getChoice();
//void menuLoop( Min3Heap& min3Heap );
//void insertItem( Min3Heap& min3Heap );
//void deleteItem( Min3Heap& min3Heap );
//void deletemin( Min3Heap& min3Heap );
//void deletemax( Min3Heap& min3Heap );
//void printLevelOrder( Min3Heap& min3Heap );
//
//int main()
//{
//    long anlongeger;
//    std::ifstream fileReader( "data.txt" );
//
//    if( fileReader.is_open() )
//    {
//        Queue<long> readValues;
//
//        while( fileReader >> anlongeger )
//        {
//            readValues.enqueue( anlongeger );
//        }
//
//        Min3Heap min3Heap( 200, readValues );
//
//        menuLoop( min3Heap );
//        fileReader.close();
//    }
//    else
//    {
//        std::cout << "Error reading file\n";
//    }
//
//    return 0;
//}
//
//void menuLoop( Min3Heap& min3Heap )
//{
//    long choice = 0;
//
//    while( choice != 6 )
//    {
//        choice = getChoice();
//
//        switch( choice )
//        {
//        case 1:
//            insertItem( min3Heap );
//            break;
//        case 2:
//            deletemin( min3Heap );
//            break;
//        case 3:
//            deletemax( min3Heap );
//            break;
//        case 4:
//            deleteItem( min3Heap );
//            break;
//        case 5:
//            printLevelOrder( min3Heap );
//            break;
//        default:
//            if( choice != 6 )
//            {
//                std::cout << "Enter a valid choice (1-5)\n";
//            }
//            break;
//        }
//    }
//}
//
//long getChoice()
//{
//    long choice = 0;
//
//    std::cout << "..........................................................\n";
//    std::cout << "Please choose one of the folowing commands:\n";
//    std::cout << "1 - insert\n"
//        << "2 - deletemin\n"
//        << "3 - deletemax\n"
//        << "4 - remove\n"
//        << "5 - levelorder\n"
//        << "6 - exit\n"
//        << "\n";
//
//    std::cin >> choice;
//
//    return choice;
//}
//
//void insertItem( Min3Heap& min3Heap )
//{
//    std::cout << "Choose a number to be added to the heap\n";
//    long number;
//    std::cin >> number;
//    min3Heap.insert( number );
//}
//
//void deleteItem( Min3Heap& min3Heap )
//{
//    std::cout << "Choose a number to be removed from the heap\n";
//    long number;
//    std::cin >> number;
//    if( !min3Heap.remove( number ) )
//    {
//        std::cout << "Error, cannot delete " << number << ", value is not in the heap.\n";
//    }
//}
//
//void deletemin( Min3Heap& min3Heap )
//{
//    if( min3Heap.deleteMin() == -1 )
//    {
//        std::cout << "The heap is empty\n";
//    }
//}
//
//void deletemax( Min3Heap& min3Heap )
//{
//    if( min3Heap.deleteMax() == -1)
//    {
//        std::cout << "The heap is empty\n";
//    }
//}
//
//void printLevelOrder( Min3Heap& min3Heap )
//{
//    std::cout << "Level Order:\n";
//    min3Heap.levelOrderDisplay();
//    std::cout << std::endl;
//}

class Timer
{
private:

    timeval startTime;
    timeval endTime;

public:

    void start()
    {
        gettimeofday( &startTime, NULL );
    }

    double stop()
    {
        long seconds, nseconds;
        double duration;

        gettimeofday( &endTime, NULL );

        seconds = endTime.tv_sec - startTime.tv_sec;
        nseconds = endTime.tv_usec - startTime.tv_usec;

        duration = seconds + nseconds / 1000000.0;

        return duration;
    }

    void printTime(double duration)
    {
        printf( "%5.6f seconds\n", duration );
    }
};

int main()
{
    Timer myTimer;
    double heapBuildDuration[20];
    double treeBuildDuration[20];
    double heapOperationsDuration[20] = { };
    double bstOperationsDuration[20] = { };

    long nValues[] = { 50000, 100000, 200000, 400000 };

    for( unsigned int i = 0; i < 4; i++ )
    {
        long n = nValues[i];
        long* testArray = new long[n];

        for( int j = 0; j < 5; j++ )
        {
            srand( j + 5 );
            int currentDurationIndex = i * 5 + j;

            for( long k = 0; k < n; k++ )
            {
                testArray[k] = ( rand() % ( 4 * n ) ) + 1;
            }

            myTimer.start();
            Min3Heap min3Heap( n, testArray, n );
            heapBuildDuration[currentDurationIndex] = myTimer.stop();

            myTimer.start();
            BinarySearchTree bst;
            for( long k = 0; k < n; k++ )
            {
                bst.insert( testArray[k] );
            }
            treeBuildDuration[currentDurationIndex] = myTimer.stop();

            double x = rand() / (double) RAND_MAX;

            if( x >= 0 && x < 0.1 )
            {
                for( long z = 0; z < ( 0.1 * n ); z++ )
                {
                    myTimer.start();
                    min3Heap.deleteMin();
                    heapOperationsDuration[currentDurationIndex] += myTimer.stop();

                    myTimer.start();
                    bst.deletemin();
                    bstOperationsDuration[currentDurationIndex] += myTimer.stop();
                }

            }
            else if( x >= 0.1 && x < 0.2 )
            {
                for( long z = 0; z < ( 0.1 * n ); z++ )
                {
                    myTimer.start();
                    min3Heap.deleteMax();
                    heapOperationsDuration[currentDurationIndex] += myTimer.stop();

                    myTimer.start();
                    bst.deletemax();
                    bstOperationsDuration[currentDurationIndex] += myTimer.stop();
                }
            }
            else if( x >= 0.2 && x < 0.5 )
            {
                long valueToRemove = ( rand() % ( 4 * n ) ) + 1;


                myTimer.start();
                min3Heap.remove( valueToRemove );
                heapOperationsDuration[currentDurationIndex] = myTimer.stop();

                myTimer.start();
                bst.removeAll( valueToRemove );
                bstOperationsDuration[currentDurationIndex] = myTimer.stop();
            }
            else
            {
                for( long z = 0; z < ( 0.1 * n ); z++ )
                {
                    long valueToInsert = ( rand() % ( 4 * n ) ) + 1;

                    myTimer.start();
                    min3Heap.insert( valueToInsert );
                    heapOperationsDuration[currentDurationIndex] = myTimer.stop();

                    myTimer.start();
                    bst.insert( valueToInsert );
                    bstOperationsDuration[currentDurationIndex] = myTimer.stop();
                }
            }
        }

        std::cout << std::endl;
        delete[] testArray;
    }

    for( int i = 0; i < 4; i++ )
    {
        // double openAverage = 0;
        // double quadraticAverage = 0;
        // double doubleAverage = 0;
        double heapBuildSum = 0;
        double bstBuildSum = 0;
        double heapOperationsSum = 0;
        double bstOperationsSum = 0;

        for( int j = 0; j < 5; j++ )
        {
            heapBuildSum += heapBuildDuration[( i * 5 + j )];
            bstBuildSum += treeBuildDuration[( i * 5 + j )];
            heapOperationsSum += heapOperationsDuration[( i * 5 + j )];
            bstOperationsSum += bstOperationsDuration[( i * 5 + j )];
        }

        std::cout << "For n = " << nValues[i] << ":" << std::endl;
        std::cout << "\tHeap Build Average is: " << ( heapBuildSum / 5 ) << "s" << std::endl;
        std::cout << "\tBST Build Average is: " << ( bstBuildSum / 5 ) << "s" << std::endl;
        std::cout << "\tHeap Operations Average is: " << ( heapOperationsSum / 5 ) << "s"
                << std::endl;
        std::cout << "\tBST Operations Average is: " << ( bstOperationsSum / 5 ) << "s"
                << std::endl;
        std::cout << std::endl;
    }

    return 0;
}

