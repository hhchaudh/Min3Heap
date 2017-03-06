#ifndef MIN_3_HEAP_H
#define MIN_3_HEAP_H

#include "Queue.h"

class Min3Heap
{
public:
    Min3Heap( int aSize );
    Min3Heap( int aSize, Queue<int>& aQueue );
    Min3Heap( int aSize, int values[], int valuesSize );
    ~Min3Heap();
    int search( int aSearchValue );
    void bottomUpInsert( const int aValue );
    void insert( const int aValue );
    bool remove( const int aValue );
    void levelOrderDisplay();
    int deleteMin();
    int deleteMax();
private:
    int findSmallestChildIndex( int aValueToMove, int aIndex ) const;
    void search( int aSearchVal, int aIndex, int& aFoundIndex );
    void heapifyDown( const int aValueToMove, const int aIndex );
    void heapifyUp( int aValueToMove, int aIndex );
    bool isParent( int aIndex ) const;
    int getParent( int aIndex ) const;
    bool nthChildExists( int aIndex, int nthChild ) const;
    int getNthChild( int aIndex, int aNthChild ) const;
    int pow( const int exponent ) const;
    bool isEmpty() const;
    int findMaxIndex();
    int lastParentIndex();
    int mNumNodes;
    const unsigned int mSIZE;
    int* mHeapArray;
};
#endif // !MIN_3_HEAP_H
