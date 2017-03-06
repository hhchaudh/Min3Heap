#include "Min3Heap.h"
#include <iostream>

Min3Heap::Min3Heap( long aSize ) :
    mSIZE( aSize ),
    mNumNodes( 0 ),
    mHeapArray( new long[aSize] )
{
}

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

Min3Heap::Min3Heap( long aSize, long values[], long valuesSize ) :
    mSIZE(aSize),
    mNumNodes(0),
    mHeapArray(new long[aSize])
{
    std::cout << "Inserting with size " << aSize << std::endl;
    for( long i = 0; i < valuesSize; i++ )
    {
        bottomUpInsert( values[i] );
    }

    for( long i = lastParentIndex(); i >= 0; i-- )
    {
        heapifyDown( mHeapArray[i], i );
    }
}

Min3Heap::~Min3Heap()
{
    delete[] mHeapArray;
}

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

void Min3Heap::bottomUpInsert( const long aValue )
{
    mHeapArray[mNumNodes] = aValue;
    mNumNodes++;
}

void Min3Heap::insert( const long aValue )
{
    if(mNumNodes == mSIZE)
    {
        return;
    }
    bottomUpInsert( aValue );
    heapifyUp( aValue, mNumNodes - 1 );
}

bool Min3Heap::remove( const long aValue )
{
    long indexOfValue = -1;
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
            long valueToMove = mHeapArray[indexOfValue];
            mHeapArray[mNumNodes - 1] = -1;
            mNumNodes--;

            long parentIndex = getParent( indexOfValue );

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
    long nodeCount = 0;

    for( long i = 0; i < mNumNodes; i++ )
    {
        long valuesPerLevel = pow( i );

        for( long j = 0; j < valuesPerLevel; j++ )
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

    // for(long i = 0; i < mSIZE; i++)
    // {
    //     if(mHeapArray[i] == aSearchVal)
    //     {
    //         aFoundIndex = i;
    //         return;
    //     }
    // }
}

void Min3Heap::heapifyDown( const long aValueToMove, const long aIndex )
{
    long smallestChildIndex = findSmallestChildIndex( aValueToMove, aIndex );

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

void Min3Heap::heapifyUp( long aValueToMove, long aIndex )
{
    long parentIndex = getParent( aIndex );

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

bool Min3Heap::isParent( long aIndex ) const
{
    return ( ( aIndex * 3 ) < ( mNumNodes - 1 ) );
}

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

bool Min3Heap::nthChildExists( long aIndex, long aNthChild ) const
{
    return ( ( 3 * aIndex + aNthChild ) < mNumNodes );
}

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

bool Min3Heap::isEmpty() const
{
    return ( mNumNodes > 0 );
}

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

long Min3Heap::lastParentIndex()
{
    return ( ( mNumNodes - 2 ) / 3 );
}

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
