#include "Min3Heap.h"
#include <iostream>

// Simple constructor that creates an empty array of size aSize
Min3Heap::Min3Heap( long aSize ) :
    mSIZE( aSize ),
    mNumNodes( 0 ),
    mHeapArray( new long[aSize] )
{
}

// This constructor is used when reading values from a file
// Easier that using an array since we don't know how many numbers we'll read
// First insert values as they're given, then go to the first parent and begin
// heapifying down from the last parent to the first
Min3Heap::Min3Heap( long aSize, Queue<long>& aQueue ) :
    mSIZE( aSize ),
    mNumNodes( 0 ),
    mHeapArray( new long[aSize] )
{
    while( !aQueue.isEmpty() )
    {
        bottomUpInsert( aQueue.peekFront() );
        aQueue.dequeue();
    }

    for( long i = lastParentIndex(); i >= 0; i-- )   //mNumNodes is the size of the array, the last used index is mNumNodes - 1
    {
        heapifyDown( mHeapArray[i], i );
    }
}

// This constructor uses an array to construct the heap
// First insert each value in the array in order, and then
// find the last parent and heapify downward for each parent
// starting from the last to the first
Min3Heap::Min3Heap( long aSize, long values[], long valuesSize ) :
    mSIZE(aSize),
    mNumNodes(0),
    mHeapArray(new long[aSize])
{
    for( long i = 0; i < valuesSize; i++ )
    {
        bottomUpInsert( values[i] );
    }

    for( long i = lastParentIndex(); i >= 0; i-- )
    {
        heapifyDown( mHeapArray[i], i );
    }
}

// The destructor, destroys the heap array
Min3Heap::~Min3Heap()
{
    delete[] mHeapArray;
}

// The search function, checks if the heap is empty before sending values to the
// recursive search function
long Min3Heap::search( long aSearchValue )
{
    long foundIndex = -1;

    if( mNumNodes < 1 )
    {
        return -1;
    }
    else
    {
        search( aSearchValue, 0, foundIndex );
    }

    return foundIndex;
}

// bottomUpInsert simply inserts values in the heap
// without heapifying
void Min3Heap::bottomUpInsert( const long aValue )
{
    mHeapArray[mNumNodes] = aValue;
    mNumNodes++;
}

// Inserts values into the heap, and then heapifies
void Min3Heap::insert( const long aValue )
{
    if(mNumNodes == mSIZE)
    {
        return;
    }
    bottomUpInsert( aValue );
    heapifyUp( aValue, mNumNodes - 1 );
}

// Removes values from the heap
bool Min3Heap::remove( const long aValue )
{
    long indexOfValue = -1;         // Initial index location, used as a flag
    bool aValRemoved = false;       // If we remove at least one value, then we switch this to true

    do                              // Do at least once iteration of this loop   
    {               
        indexOfValue = search( aValue );    // Search for the index of aValue

        if( indexOfValue == 0 )     // If it's the first value, use deleteMin()
        {
            aValRemoved = true;     // We removed a value, return true
            deleteMin();
        }
        else if( indexOfValue > -1 )    // indexOfValue is greater than -1 when we found a value
        {
            aValRemoved = true;
            mHeapArray[indexOfValue] = mHeapArray[mNumNodes - 1];   // Swap current index value with the last index value
            long valueToMove = mHeapArray[indexOfValue];            // We have a new valueToMove
            mHeapArray[mNumNodes - 1] = -1;                         // Turn the last value into a -1, indicating it's "empty"
            mNumNodes--;                                            // Reduce the number of nodes we have in the heap

            long parentIndex = getParent( indexOfValue );           // Get the parent of the current index

            if( parentIndex > -1 && ( indexOfValue != mNumNodes ) ) // Make a decision on which way to heapify
            {
                if( valueToMove < mHeapArray[parentIndex] )
                {
                    heapifyUp( valueToMove, indexOfValue );
                }
                else if( valueToMove > mHeapArray[parentIndex] )
                {
                    heapifyDown( valueToMove, indexOfValue );
                }
            }
        }
    } while( indexOfValue > -1 );

    return aValRemoved;                                             // Return the flag indicating if a value was removed
}

void Min3Heap::levelOrderDisplay()                                  // Displays values in order
{
    long nodeCount = 0;

    for( long i = 0; i < mNumNodes; i++ )
    {
        long valuesPerLevel = pow( i );                             // Each level contains (3 ^ level) values

        for( long j = 0; j < valuesPerLevel; j++ )
        {
            std::cout << mHeapArray[nodeCount] << " ";
            nodeCount++;

            if( ( ( j + 1 ) % 3 == 0 ) && ( j != 0 ) && ( j != valuesPerLevel - 1 ) && nodeCount != mNumNodes )
            {
                std::cout << "- ";
            }
            if( nodeCount == mNumNodes )                            // Stop displaying if we reache the end of the heap
            {
                std::cout << std::endl;
                return;
            }
        }

        std::cout << std::endl;
    }
}

// replaces the top value with the last value then heapifies
long Min3Heap::deleteMin()                                          
{
    if( mNumNodes > 0 )
    {
        long minValue = mHeapArray[0];
        mHeapArray[0] = mHeapArray[mNumNodes - 1];
        mHeapArray[mNumNodes - 1] = -1;
        mNumNodes--;
        heapifyDown( mHeapArray[0], 0 );
        return minValue;
    }

    return -1;
}

// Finds the max value among the leaves
// Deletes the value and replaces with last value
// Check for heapification
long Min3Heap::deleteMax()
{
    long maxValue = -1;

    if( mNumNodes > 0 )
    {
        if( mNumNodes == 1 )
        {
            maxValue = mHeapArray[0];
            mHeapArray[0] = -1;
            mNumNodes--;
        }
        else
        {
            long maxIndex = findMaxIndex();
            maxValue = mHeapArray[maxIndex];
            mHeapArray[maxIndex] = mHeapArray[mNumNodes - 1];
            mHeapArray[mNumNodes - 1] = -1;
            mNumNodes--;

            long parentIndex = getParent( maxIndex );

            if( parentIndex > -1 && ( maxIndex != mNumNodes ) )
            {
                if( mNumNodes > 0 )
                {
                    if( mHeapArray[maxIndex] < mHeapArray[parentIndex] )
                    {
                        heapifyUp( mHeapArray[maxIndex], maxIndex );
                    }
                }
            }
        }
    }

    return maxValue;
}

// Recursive search, check if the current value's children are 
// greater, if so, then we should not purse further down the subtree
// that is rooted by that child
void Min3Heap::search( long aSearchVal, long aIndex, long & aFoundIndex )
{
    if( aFoundIndex > -1 )
    {
        return;
    }
    else if( aSearchVal == mHeapArray[aIndex] )
    {
        aFoundIndex = aIndex;
        return;
    }
    else if( aSearchVal > mHeapArray[aIndex] )
    {
        for( long i = 1; i <= 3; i++ )
        {
            if(getNthChild(aIndex, i) > -1)
            {
                search( aSearchVal, getNthChild( aIndex, i ), aFoundIndex );
            }
        }
    }
}

// Heapify downward
void Min3Heap::heapifyDown( const long aValueToMove, const long aIndex )
{
    long smallestChildIndex = findSmallestChildIndex( aValueToMove, aIndex );

    if( smallestChildIndex > -1 )       // If smallestChildIndex returned -1, that means there are no smaller children
    {
        mHeapArray[aIndex] = mHeapArray[smallestChildIndex];

        if( isParent( smallestChildIndex ) )
        {
            heapifyDown( aValueToMove, smallestChildIndex );
        }
        else
        {
            mHeapArray[smallestChildIndex] = aValueToMove;
        }
    }
    else
    {
        mHeapArray[aIndex] = aValueToMove;
    }
}

// Heapify up
void Min3Heap::heapifyUp( long aValueToMove, long aIndex )
{
    long parentIndex = getParent( aIndex );

    if( parentIndex > -1 )                  // If the parentIndex is -1, that means there is no parent
    {
        if( aValueToMove < mHeapArray[parentIndex] )
        {
            mHeapArray[aIndex] = mHeapArray[parentIndex];
            heapifyUp( aValueToMove, parentIndex );
        }
        else
        {
            mHeapArray[aIndex] = aValueToMove;
        }
    }
    else
    {
        mHeapArray[aIndex] = aValueToMove;
    }
}

// Use k*i < n-1 to check for parent status, k=3
bool Min3Heap::isParent( long aIndex ) const
{
    return ( ( aIndex * 3 ) < ( mNumNodes - 1 ) );
}

// Use (i-1)/k to get parent, k=3
long Min3Heap::getParent( long aIndex ) const
{
    if( aIndex > 0 )
    {
        return ( ( aIndex - 1 ) / 3 );
    }
    else
    {
        return -1;
    }
}

// Check if the aNthChild exists
bool Min3Heap::nthChildExists( long aIndex, long aNthChild ) const
{
    return ( ( 3 * aIndex + aNthChild ) < mNumNodes );
}

// Get the aNthChild
long Min3Heap::getNthChild( long aIndex, long aNthChild ) const
{
    if( nthChildExists( aIndex, aNthChild ) )
    {
        return 3 * aIndex + aNthChild;
    }
    else
    {
        return -1;
    }
}

// Calculates powers of 3
long Min3Heap::pow( const long exponent ) const
{
    if( exponent == 0 )
    {
        return 1;
    }
    else
    {
        long returnValue = 1;

        for( long i = 0; i < exponent; i++ )
        {
            returnValue *= 3;
        }

        return returnValue;
    }
}

// Check if the heap is empty
bool Min3Heap::isEmpty() const
{
    return ( mNumNodes > 0 );
}

// Find the index of the maximum value, search and compare each leaf
long Min3Heap::findMaxIndex()
{
    long maxValIndex = lastParentIndex() + 1;

    for( long i = lastParentIndex() + 2; i < mNumNodes; i++ )
    {
        if( mHeapArray[i] > mHeapArray[maxValIndex] )
        {
            maxValIndex = i;
        }
    }

    return maxValIndex;
}

// Find the index of the last parent
long Min3Heap::lastParentIndex()
{
    return ( ( mNumNodes - 2 ) / 3 );
}

// Find the index of the smallest child
long Min3Heap::findSmallestChildIndex( long aValueToMove, long aIndex ) const
{
    if( isParent( aIndex ) )
    {
        long childIndices[3];

        for( long i = 1; i <= 3; i++ )
        {
            long ithChildIndex = getNthChild( aIndex, i );

            if( ithChildIndex > -1 )
            {
                childIndices[i - 1] = mHeapArray[ithChildIndex];
            }
            else
            {
                childIndices[i - 1] = -1;
            }
        }

        long minValueIndex = -1;

        for( long i = 0; i < 3; i++ )
        {
            if( aValueToMove > childIndices[i] && childIndices[i] != -1 )
            {
                if( minValueIndex == -1 || ( childIndices[i] < childIndices[minValueIndex] ) )
                {
                    minValueIndex = i;      // minValueIndex has the potential to stay at -1 here, indicating no smaller children
                }
            }
        }

        if( minValueIndex > -1 )
        {
            return ( getNthChild( aIndex, minValueIndex + 1 ) );
        }
        else
        {
            return -1;
        }
    }
    else
    {
        return -1;
    }
}
