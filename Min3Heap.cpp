#include "Min3Heap.h"
#include <iostream>

Min3Heap::Min3Heap( int aSize ) :
    mSIZE( aSize ),
    mNumNodes( 0 ),
    mHeapArray( new int[aSize] )
{
}

Min3Heap::Min3Heap( int aSize, Queue<int>& aQueue ) :
    mSIZE( aSize ),
    mNumNodes( 0 ),
    mHeapArray( new int[aSize] )
{
    while( !aQueue.isEmpty() )
    {
        bottomUpInsert( aQueue.peekFront() );
        aQueue.dequeue();
    }

    for( int i = lastParentIndex(); i >= 0; i-- )   //mNumNodes is the size of the array, the last used index is mNumNodes - 1
    {
        heapifyDown( mHeapArray[i], i );
    }
}

Min3Heap::Min3Heap( int aSize, int values[], int valuesSize ) :
    mSIZE(aSize),
    mNumNodes(0),
    mHeapArray(new int[aSize])
{
    for( int i = 0; i < valuesSize; i++ )
    {
        bottomUpInsert( values[i] );
    }

    for( int i = lastParentIndex(); i >= 0; i-- )
    {
        heapifyDown( mHeapArray[i], i );
    }
}

Min3Heap::~Min3Heap()
{
    delete[] mHeapArray;
}

int Min3Heap::search( int aSearchValue )
{
    int foundIndex = -1;

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

void Min3Heap::bottomUpInsert( const int aValue )
{
    mHeapArray[mNumNodes] = aValue;
    mNumNodes++;
}

void Min3Heap::insert( const int aValue )
{
    bottomUpInsert( aValue );
    heapifyUp( aValue, mNumNodes - 1 );
}

bool Min3Heap::remove( const int aValue )
{
    int indexOfValue = -1;
    bool aValRemoved = false;

    do
    {
        indexOfValue = search( aValue );

        if( indexOfValue == 0 )
        {
            aValRemoved = true;
            deleteMin();
        }
        else if( indexOfValue > -1 )
        {
            aValRemoved = true;
            mHeapArray[indexOfValue] = mHeapArray[mNumNodes - 1];
            int valueToMove = mHeapArray[indexOfValue];
            mHeapArray[mNumNodes - 1] = -1;
            mNumNodes--;

            int parentIndex = getParent( indexOfValue );

            if( parentIndex > -1 && ( indexOfValue != mNumNodes ) )
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

    return aValRemoved;
}

void Min3Heap::levelOrderDisplay()
{
    int nodeCount = 0;

    for( int i = 0; i < mNumNodes; i++ )
    {
        int valuesPerLevel = pow( i );

        for( int j = 0; j < valuesPerLevel; j++ )
        {
            std::cout << mHeapArray[nodeCount] << " ";
            nodeCount++;

            if( ( ( j + 1 ) % 3 == 0 ) && ( j != 0 ) && ( j != valuesPerLevel - 1 ) && nodeCount != mNumNodes )
            {
                std::cout << "- ";
            }
            if( nodeCount == mNumNodes )
            {
                std::cout << std::endl;
                return;
            }
        }

        std::cout << std::endl;
    }
}

int Min3Heap::deleteMin()
{
    if( mNumNodes > 0 )
    {
        int minValue = mHeapArray[0];
        mHeapArray[0] = mHeapArray[mNumNodes - 1];
        mHeapArray[mNumNodes - 1] = -1;
        mNumNodes--;
        heapifyDown( mHeapArray[0], 0 );
        return minValue;
    }

    return -1;
}

int Min3Heap::deleteMax()
{
    int maxValue = -1;

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
            int maxIndex = findMaxIndex();
            maxValue = mHeapArray[maxIndex];
            mHeapArray[maxIndex] = mHeapArray[mNumNodes - 1];
            mHeapArray[mNumNodes - 1] = -1;
            mNumNodes--;

            int parentIndex = getParent( maxIndex );

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

void Min3Heap::search( int aSearchVal, int aIndex, int & aFoundIndex )
{
    if( aIndex == -1 )
    {
        return;
    }

    if( aFoundIndex > -1 )
    {
        return;
    }

    if( aSearchVal == mHeapArray[aIndex] )
    {
        aFoundIndex = aIndex;
        return;
    }

    if( aSearchVal > mHeapArray[aIndex] )
    {
        for( int i = 1; i <= 3; i++ )
        {
            search( aSearchVal, getNthChild( aIndex, i ), aFoundIndex );
        }
    }
}

void Min3Heap::heapifyDown( const int aValueToMove, const int aIndex )
{
    int smallestChildIndex = findSmallestChildIndex( aValueToMove, aIndex );

    if( smallestChildIndex > -1 )
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

void Min3Heap::heapifyUp( int aValueToMove, int aIndex )
{
    int parentIndex = getParent( aIndex );

    if( parentIndex > -1 )
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

bool Min3Heap::isParent( int aIndex ) const
{
    return ( ( aIndex * 3 ) < ( mNumNodes - 1 ) );
}

int Min3Heap::getParent( int aIndex ) const
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

bool Min3Heap::nthChildExists( int aIndex, int nthChild ) const
{
    return ( ( 3 * aIndex + nthChild ) < mNumNodes );
}

int Min3Heap::getNthChild( int aIndex, int aNthChild ) const
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

int Min3Heap::pow( const int exponent ) const
{
    if( exponent == 0 )
    {
        return 1;
    }
    else
    {
        int returnValue = 1;

        for( int i = 0; i < exponent; i++ )
        {
            returnValue *= 3;
        }

        return returnValue;
    }
}

bool Min3Heap::isEmpty() const
{
    return ( mNumNodes > 0 );
}

int Min3Heap::findMaxIndex()
{
    int maxValIndex = lastParentIndex() + 1;

    for( int i = lastParentIndex() + 2; i < mNumNodes; i++ )
    {
        if( mHeapArray[i] > mHeapArray[maxValIndex] )
        {
            maxValIndex = i;
        }
    }

    return maxValIndex;
}

int Min3Heap::lastParentIndex()
{
    return ( ( mNumNodes - 2 ) / 3 );
}

int Min3Heap::findSmallestChildIndex( int aValueToMove, int aIndex ) const
{
    if( isParent( aIndex ) )
    {
        int childIndices[3];

        for( int i = 1; i <= 3; i++ )
        {
            int ithChildIndex = getNthChild( aIndex, i );

            if( ithChildIndex > -1 )
            {
                childIndices[i - 1] = mHeapArray[ithChildIndex];
            }
            else
            {
                childIndices[i - 1] = -1;
            }
        }

        int minValueIndex = -1;

        for( int i = 0; i < 3; i++ )
        {
            if( aValueToMove > childIndices[i] && childIndices[i] != -1 )
            {
                if( minValueIndex == -1 || ( childIndices[i] < childIndices[minValueIndex] ) )
                {
                    minValueIndex = i;
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
