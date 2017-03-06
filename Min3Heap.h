#ifndef MIN_3_HEAP_H
#define MIN_3_HEAP_H

#include "Queue.h"

class Min3Heap
{
public:
    Min3Heap( long aSize );
    Min3Heap( long aSize, Queue<long>& aQueue );
    Min3Heap( long aSize, long values[], long valuesSize );
    ~Min3Heap();
    long search( long aSearchValue );
    void bottomUpInsert( const long aValue );
    void insert( const long aValue );
    bool remove( const long aValue );
    void levelOrderDisplay();
    long deleteMin();
    long deleteMax();
private:
    long findSmallestChildIndex( long aValueToMove, long aIndex ) const;
    void search( long aSearchVal, long aIndex, long& aFoundIndex );
    void heapifyDown( const long aValueToMove, const long aIndex );
    void heapifyUp( long aValueToMove, long aIndex );
    bool isParent( long aIndex ) const;
    long getParent( long aIndex ) const;
    bool nthChildExists( long aIndex, long nthChild ) const;
    long getNthChild( long aIndex, long aNthChild ) const;
    long pow( const long exponent ) const;
    bool isEmpty() const;
    long findMaxIndex();
    long lastParentIndex();

    long mNumNodes;
    const long mSIZE;
    long* mHeapArray;
};
#endif // !MIN_3_HEAP_H
