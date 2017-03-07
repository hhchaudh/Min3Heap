#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "Min3Heap.h"
#include "BinarySearchTree.h"

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
    double bstBuildDuration[20];
    double heapOperationsDuration[20] = { };
    double bstOperationsDuration[20] = { };
    double x;

    long nValues[] = { 50000, 100000, 200000, 400000 };

    for( unsigned int i = 0; i < 4; i++ )
    {
        long n = nValues[i];

        for( int j = 0; j < 5; j++ )
        {
            srand( j + 15 );
            int currentDurationIndex = i * 5 + j;
            long* testArray = new long[n];

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
            bstBuildDuration[currentDurationIndex] = myTimer.stop();

            for( long z = 0; z < ( 0.1 * n ); z++ )
            {
                x = rand() / (double) RAND_MAX;

                if( x >= 0 && x < 0.5 )
                {
                    myTimer.start();
                    min3Heap.deleteMin();
                    heapOperationsDuration[currentDurationIndex] += myTimer.stop();

                    myTimer.start();
                    bst.deletemin();
                    bstOperationsDuration[currentDurationIndex] += myTimer.stop();
                }
                else if( x >= 0.1 && x < 2 )
                {
                    myTimer.start();
                    min3Heap.deleteMax();
                    heapOperationsDuration[currentDurationIndex] += myTimer.stop();

                    myTimer.start();
                    bst.deletemax();
                    bstOperationsDuration[currentDurationIndex] += myTimer.stop();
                }
                else if( x >= 0.2 && x < 0.5 )
                {
                    long valueToRemove = ( rand() % ( 4 * n ) ) + 1;

                    myTimer.start();
                    min3Heap.remove( valueToRemove );
                    heapOperationsDuration[currentDurationIndex] += myTimer.stop();

                    myTimer.start();
                    bst.removeAll( valueToRemove );
                    bstOperationsDuration[currentDurationIndex] += myTimer.stop();
                }
                else
                {
                    long valueToInsert = ( rand() % ( 4 * n ) ) + 1;

                    myTimer.start();
                    min3Heap.insert( valueToInsert );
                    heapOperationsDuration[currentDurationIndex] += myTimer.stop();

                    myTimer.start();
                    bst.insert( valueToInsert );
                    bstOperationsDuration[currentDurationIndex] += myTimer.stop();
                }
            }

            delete[] testArray;
        }
        std::cout << "Complete loop " << i << " with n: " << n << std::endl;
        std::cout << std::endl;
    }

    for( int i = 0; i < 4; i++ )
    {
        double heapBuildSum = 0;
        double bstBuildSum = 0;
        double heapOperationsSum = 0;
        double bstOperationsSum = 0;

        for( int j = 0; j < 5; j++ )
        {
            int currentDurationIndex = i * 5 + j;

            heapBuildSum += heapBuildDuration[currentDurationIndex];
            bstBuildSum += bstBuildDuration[currentDurationIndex];
            heapOperationsSum += heapOperationsDuration[currentDurationIndex];
            bstOperationsSum += bstOperationsDuration[currentDurationIndex];
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

