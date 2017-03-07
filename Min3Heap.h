/**
*	@file : Min3Heap.h
*	@author :  Haaris Chaudhry
*	@date : Mar 6, 2017
*	Purpose: The Min3Heap class will simulate the classical functions k-heap with k equal to 3
*            Other functions like deleteMax, search, and remove have been added.
*/

#ifndef MIN_3_HEAP_H
#define MIN_3_HEAP_H

#include "Queue.h"

class Min3Heap
{
public:
    /**
    * Constructor for the Min3Heap
    * @param aSize The size of the array that will contain the heap values
    * @return A Min 3-heap with a size of aSize
    */
    Min3Heap( long aSize );

    /**
    * Constructor for the Min3Heap
    * @param aSize The size of the array that will contain the heap values
    * @param aQueue This queue is used when values need to be read from a file
    * @return A Min 3-heap with a size of aSize containing the values in aQueue
    */
    Min3Heap( long aSize, Queue<long>& aQueue );

    /**
    * Constructor for the Min3Heap
    * @param aSize The size of the array that will contain the heap values
    * @param aQueue This queue is used when values need to be read from a file
    * @param values an array of values to be inserted into the heap
    * @param valuesSize the size of the array
    * @return A Min 3-heap with a size of aSize containing the values in values
    */
    Min3Heap( long aSize, long values[], long valuesSize );

    /**
    * The destructor
    */
    ~Min3Heap();

    /**
    * A search function that finds the index of the value to be searched
    * @param aSearchValue The value to search for
    * @return The index of the searched value (returns -1 if not found)
    */
    long search( long aSearchValue );

    /**
    * A function used to insert values without heapifying, used during bottom up construction
    * @param aValue The value to be inserted into the heap
    */
    void bottomUpInsert( const long aValue );

    /**
    * The insertion function, also heapifies the value
    * @param aValue The value to be inserted
    */
    void insert( const long aValue );

    /**
    * A function that removes an arbitrary value
    * @param aValue The value to be removed
    * @return True if the value was removed, false otherwise
    */
    bool remove( const long aValue );

    /**
    * Displays the heap in a fancy level order using hyphens
    */
    void levelOrderDisplay();

    /**
    * Deletes the minimum value
    * @return The value that was deleted
    */
    long deleteMin();

    /**
    * Deletes the maximum value
    * @return The value that was deleted
    */
    long deleteMax();
private:
    /**
    * Finds the smallest child of the given given index
    * @param aValueToMove The value that we'll compare against
    * @param aIndex The index of the node that we'll compare against aValueToMove
    * @return The smallest child of the given index, returns -1 if there are no smaller children
    */
    long findSmallestChildIndex( long aValueToMove, long aIndex ) const;

    /**
    * Search for a particular value
    * @param aSearchVal The value to search for
    * @param aIndex The index that we're currently searching from
    * @param aFoundIndex The index of the value if we find it
    */
    void search( long aSearchVal, long aIndex, long& aFoundIndex );

    /**
    * Heapifies downward
    * @param aValueToMove The value to be heapified
    * @param aIndex The current index that we're heapifying from
    */
    void heapifyDown( const long aValueToMove, const long aIndex );

    /**
    * Heapifies upward
    * @param aValueToMove The value to be heapified
    * @param aIndex The current index that we're heapifying from
    */
    void heapifyUp( long aValueToMove, long aIndex );

    /**
    * Checks if the current node is a parent
    * @param aIndex The index of the current node
    * @return True if the node is a parent, false if otherwise
    */
    bool isParent( long aIndex ) const;

    /**
    * Gets the parent node index
    * @param aIndex The index of the current node
    * @return The index of the parent (-1 if there is no parent)
    */
    long getParent( long aIndex ) const;

    /**
    * Checks if a particular child (either 1, 2, or 3) exists
    * @param aIndex The index to check for children on
    * @param nthChild The child index that we're searching for (either 1, 2, or 3)
    * @return A flag indicating if a child does indeed exist (true if so, false if not)
    */
    bool nthChildExists( long aIndex, long nthChild ) const;

    /**
    * Retreives the index of the child
    * @param aIndex The index of the parent
    * @param aNthChild The child that we're searching for
    * @return The index of the chil;d
    */
    long getNthChild( long aIndex, long aNthChild ) const;

    /**
    * Helper function that computes powers of 3
    * @param exponent The power to raise 3 to
    * @return A power of 3
    */
    long pow( const long exponent ) const;

    /**
    * Function that indicates if the heap is empty
    * @return True if empty, false if not
    */
    bool isEmpty() const;

    /**
    * Find the index of the maximum value
    * @return The value of the index containing the maximum value
    */
    long findMaxIndex();

    /**
    * Finds the index of the last parent
    * @return The index of the last parent
    */
    long lastParentIndex();

    long mNumNodes;     //!< The number of nodes in the heap
    const long mSIZE;   //!< The size of the heapArray
    long* mHeapArray;   //!< The heapArray
};
#endif // !MIN_3_HEAP_H
