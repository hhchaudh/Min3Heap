/**
*	@file : Node.h
*	@author :  Haaris Chaudhry
*	@date : 2017.2.27
*	Purpose: A simple node class for use with a binary search tree
*/

#ifndef NODE_H
#define NODE_H

class Node
{
public:
    /**
    * Node constructor
    * @param aValue The value to be inserted.
    * @return An empty Node
    */
    Node( int aValue );

    /**
    * Provides a pointer to the left child Node of the current Node
    * @return A Node pointer pointing to the left child node of the current Node
    */
    Node* getLeftChild();

    /**
    * Provides a pointer to the right child Node of the current Node
    * @return A Node pointer pointing to the right child node of the current Node
    */
    Node* getRightChild();

    /**
    * Sets the left child Node of the current Node
    * @param aNodePtr A pointer pointing to a Node that is to be used as the left child of the current node
    */
    void setLeftChild( Node* aNodePtr );

    /**
    * Sets the right child Node of the current Node
    * @param aNodePtr A pointer pointing to a Node that is to be used as the right child of the current node
    */
    void setRightChild( Node* aNodePtr );

    /**
    * Gets the value of the current Node
    * @return An integer that reflects the value contained within the Node
    */
    int getValue() const;

    /**
    * Sets the value of the current Node
    * @param aValue The value to be contained by the Node.
    */
    void setValue( int aValue );
private:
    Node* mLeftChildPtr;                //!< Pointer pointing to the left child Node
    Node* mRightChildPtr;               //!< Pointer pointing to the right child Node
    int mValue;                         //!< Value contained within the node
};

#endif