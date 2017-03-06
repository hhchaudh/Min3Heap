/**
*	@file : BinarySearchTree.h
*	@author :  Haaris Chaudhry
*	@date : 2017.2.27
*	Purpose: The BinarySearchTree class will simulate the classical functions of a binary search tree
*               while using integers as its data type.
*/

#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

#include "Node.h"
#include "Queue.h"

class BinarySearchTree
{
public:
    /**
    * The constructor, initializes all member variables to nullptr.
    * @return An empty binary search tree
    */
    BinarySearchTree();

    /**
    * The destructor. Works recursively using the postOrderDelete function.
    */
    ~BinarySearchTree();

    /**
    * Inserts values into the binary search tree.
    * @param aVal The value to be inserted.
    * @return A boolean variable indicating if insertion was successful (i.e. no duplicates were detected).
    */
    bool insert( int aVal );

    /**
    * Searches for a value in the tree.
    * @param aVal The value to be searched.
    * @return A pointer pointing to the Node that contains the value, returns nullptr if the value could not be found.
    */
    Node* search( int aVal );

    /**
    * Deletes the minimum value in the entire tree.
    * @return A boolean variable indicating if deletion was successful. (returns false if the tree is empty)
    */
    bool deletemin();

    /**
    * Deletes the maximum value in the entire tree.
    * @return A boolean variable indicating deletion was successful. (returns false if the tree is empty)
    */
    bool deletemax();

    /**
    * Removes values from the tree.
    * @param aVal The value to be removed.
    * @return A boolean variable indicating if removal was successful (returns false if the value was not found).
    */
    bool remove( int aVal );

    /**
    * Displays values in the tree using the preorder algorithm.
    */
    void preorder();

    /**
    * Displays values in the tree using the inorder algorithm.
    */
    void inorder();

    /**
    * Displays values in the tree using the levelorder algorithm.
    */
    void levelorder();
private:
    /**
    * Recursive insert
    * @param aVal The value to be inserted
    * @param aRootPtr The root of the current subtree
    * @return A boolean variable indicating successful insertion
    */
    bool insert( int aVal, Node* aRootPtr );

    /**
    * Recursive search
    * @param aVal The value to be searched
    * @param aRootPtr The root of the current subtree
    * @return A Node pointer that points to the node contain aVal
    */
    Node* search( int aVal, Node* aRootPtr );

    /**
    * Deletes the minimum value in the subtree with aRootPtr as its root
    * @param aRootPtr The root of the current subtree
    * @return The value contained within the node that was deleted.
    */
    int deleteMin( Node* aRootPtr );

    /**
    * Deletes the maximum value in the subtree with aRootPtr as its root.
    * @param aRootPtr The root of the current subtree
    * @return The value contained within the node that was deleted.
    */
    int deleteMax( Node* aRootPtr );

    /**
    * Recursive preorder
    * @param aRootPtr The root of the current subtree
    */
    void preorder( Node* aRootPtr );

    /**
    * Recursive inorder
    * @param aRootPtr The root of the current subtree
    */
    void inorder( Node* aRootPtr );

    /**
    * Recursive levelorder
    * @param aLevelOrderQ The queue that will be used throughout the recursive process to store
    *                       to children of Nodes as they are removed from the queue.
    */
    void levelorder( Queue<Node*>& aLevelOrderQ );

    /**
    * The function used to systematically destroy each node in the binary search tree.
    * @param aRootPtr The root of the current subtree
    */
    void postOrderDelete( Node* aRootPtr );

    // The root of the tree
    Node* mRoot;

    // Whenever we conduct a search, we'll save parent of the searched node. 
    Node* mSearchParent;

    // Whenever we delete the minimum value in a subtree, we'll save the parent of that deleted value
    Node* mMinParent;

    // Whenever we delete the maximum value in a subtree, we'll save the parent of that deleted value
    Node* mMaxParent;
};
#endif // !BINARY_SEARCH_TREE_H
