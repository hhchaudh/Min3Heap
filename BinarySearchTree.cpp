/**
*	@file : BinarySearchTree.cpp
*	@author :  Haaris Chaudhry
*	@date : 2017.2.27
*	Purpose: The BinarySearchTree implementation
*/

#include "BinarySearchTree.h"
#include <iostream>

BinarySearchTree::BinarySearchTree() :
    mRoot( nullptr ),
    mSearchParent( nullptr ),
    mMinParent( nullptr ),
    mMaxParent( nullptr )
{
}

BinarySearchTree::~BinarySearchTree()
{
    if( mRoot )
    {
        postOrderDelete( mRoot );
    }
}

bool BinarySearchTree::insert( int aVal )
{
    // If the tree is empty, insert at the root, otherwise search recursively for the appropriate insertion point
    if( !mRoot )
    {
        mRoot = new Node( aVal );
        return true;
    }
    else
    {
        return insert( aVal, mRoot );
    }
}

bool BinarySearchTree::insert( int aVal, Node* aRootPtr )
{
    // Straightforward check equals, then check left or right for the appropriate insertion point

    int currentValue = aRootPtr->getValue();

    if( aVal == currentValue )
    {
        return false;
    }

    if( aVal < currentValue )
    {
        if( aRootPtr->getLeftChild() )
        {
            return insert( aVal, aRootPtr->getLeftChild() );
        }
        else
        {
            aRootPtr->setLeftChild( new Node( aVal ) );
            return true;
        }
    }

    if( aVal > currentValue )
    {
        if( aRootPtr->getRightChild() )
        {
            return insert( aVal, aRootPtr->getRightChild() );
        }
        else
        {
            aRootPtr->setRightChild( new Node( aVal ) );
            return true;
        }
    }

    return false;
}

Node* BinarySearchTree::search( int aVal )
{
    // reset mSearchParent before conducting a new search
    mSearchParent = nullptr;

    if( !mRoot )
    {
        // return nullptr is the tree is empty
        return nullptr;
    }
    else
    {
        return search( aVal, mRoot );
    }
}

Node* BinarySearchTree::search( int aVal, Node* aRootPtr )
{
    // similar to insertion, except that if we find a dead end while searching, we return nullptr
    // we mSearchParent before moving on the the recursive step

    if( aVal == aRootPtr->getValue() )
    {
        return aRootPtr;
    }

    if( aVal < aRootPtr->getValue() )
    {
        if( aRootPtr->getLeftChild() )
        {
            mSearchParent = aRootPtr;
            return search( aVal, aRootPtr->getLeftChild() );
        }
        else
        {
            mSearchParent = nullptr;
            return nullptr;
        }
    }

    if( aVal > aRootPtr->getValue() )
    {
        if( aRootPtr->getRightChild() )
        {
            mSearchParent = aRootPtr;
            return search( aVal, aRootPtr->getRightChild() );
        }
        else
        {
            mSearchParent = nullptr;
            return nullptr;
        }
    }

    return nullptr;
}

bool BinarySearchTree::deletemin()
{
    // If the tree is empty, then clearly there is nothing to delete
    // otherwise, we deletemin recursively

    // remember to reset the mMinParent
    mMinParent = nullptr;

    if( !mRoot )
    {
        return false;
    }
    else
    {
        deleteMin( mRoot );
        return true;
    }
}

int BinarySearchTree::deleteMin( Node* aRootPtr )
{
    // deletemin consists of going left from aRootPtr until we can't
    // Note that if this function starts from a subtree rather than the root,
    // then we'll have to save mMinParent elsewhere.

    if( aRootPtr->getLeftChild() )
    {
        mMinParent = aRootPtr;
        return deleteMin( aRootPtr->getLeftChild() );
    }
    else
    {
        int containedValue = aRootPtr->getValue();

        if( aRootPtr->getRightChild() )
        {
            Node* rightChild = aRootPtr->getRightChild();
            if( mMinParent )
            {
                if( mMinParent->getLeftChild() == aRootPtr )
                {
                    mMinParent->setLeftChild( rightChild );
                }
                else
                {
                    mMinParent->setRightChild( rightChild );
                }
            }
            else
            {
                mRoot = rightChild;
            }
        }
        else
        {
            if( mMinParent )
            {
                mMinParent->setLeftChild( nullptr );
            }
            else
            {
                mRoot = nullptr;
            }
        }

        delete aRootPtr;
        mMinParent = nullptr;
        return containedValue;
    }
}

// Same as deletemin, except we go to the right
bool BinarySearchTree::deletemax()
{
    mMaxParent = nullptr;

    if( !mRoot )
    {
        return false;
    }
    else
    {
        deleteMax( mRoot );
        return true;
    }
}

int BinarySearchTree::deleteMax( Node* aRootPtr )
{
    if( aRootPtr->getRightChild() )
    {
        mMaxParent = aRootPtr;
        return deleteMax( aRootPtr->getRightChild() );
    }
    else
    {
        int containedValue = aRootPtr->getValue();

        if( aRootPtr->getLeftChild() )
        {
            Node* leftChild = aRootPtr->getLeftChild();
            if( mMaxParent )
            {
                mMaxParent->setRightChild( leftChild );
            }
            else
            {
                mRoot = leftChild;
            }
        }
        else
        {
            if( mMaxParent )
            {
                mMaxParent->setRightChild( nullptr );
            }
            else
            {
                mRoot = nullptr;
            }
        }

        delete aRootPtr;
        mMaxParent = nullptr;
        return containedValue;
    }
}

bool BinarySearchTree::remove( int aVal )
{
    if( mRoot )
    {
        enum childStatus
        {
            LEFT_CHILD,
            RIGHT_CHILD,
            ROOT
        }targetChildStatus;  // enum used for saving the child status of the current node

        Node* targetNode = search( aVal );  // find the current node based off the value, note that we get a parent using search
                                            // by way of mSearchParent

        // Use mSearchParent to determine what type of child the targetNode is
        if( mSearchParent )
        {
            if( mSearchParent->getLeftChild() == targetNode )
            {
                targetChildStatus = LEFT_CHILD;
            }
            else
            {
                targetChildStatus = RIGHT_CHILD;
            }
        }
        else
        {
            targetChildStatus = ROOT;
        }

        // If we found a node using a search then we go through this if block
        if( targetNode )
        {
            // The targetNode has no children, use the child status to update accordingly
            if( !( targetNode->getLeftChild() || targetNode->getRightChild() ) )
            {
                if( targetChildStatus == LEFT_CHILD )
                {
                    mSearchParent->setLeftChild( nullptr );
                }
                else if( targetChildStatus == RIGHT_CHILD )
                {
                    mSearchParent->setRightChild( nullptr );
                }
                else if( targetChildStatus == ROOT )
                {
                    mRoot = nullptr;
                }

                delete targetNode;
            }
            // The targetNode has both children, set the mMinParent as the targetNode
            // Then use deleteMin on the right subtree
            else if( targetNode->getLeftChild() && targetNode->getRightChild() )
            {
                mMinParent = targetNode;
                targetNode->setValue( deleteMin( targetNode->getRightChild() ) );
            }
            // If we just have the left child, then go through here
            else if( targetNode->getLeftChild() )
            {
                if( targetChildStatus == LEFT_CHILD )
                {
                    mSearchParent->setLeftChild( targetNode->getLeftChild() );
                }
                else if( targetChildStatus == RIGHT_CHILD )
                {
                    mSearchParent->setRightChild( targetNode->getLeftChild() );
                }
                else if( targetChildStatus == ROOT )
                {
                    mRoot = targetNode->getLeftChild();
                }

                delete targetNode;
            }
            // If we just have the right child, then go through here
            else if( targetNode->getRightChild() )
            {
                if( targetChildStatus == LEFT_CHILD )
                {
                    mSearchParent->setLeftChild( targetNode->getRightChild() );
                }
                else if( targetChildStatus == RIGHT_CHILD )
                {
                    mSearchParent->setRightChild( targetNode->getRightChild() );
                }
                else if( targetChildStatus == ROOT )
                {
                    mRoot = targetNode->getRightChild();
                }

                delete targetNode;
            }
            return true;
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }

    return false;
}

// Order traversals for output:

void BinarySearchTree::preorder()
{
    if( mRoot )
    {
        preorder( mRoot );
    }
    else
    {
        std::cout << "Nothing to print, the tree is empty.";
    }
}

void BinarySearchTree::preorder( Node* aRootPtr )
{
    std::cout << aRootPtr->getValue() << " ";

    if( aRootPtr->getLeftChild() )
    {
        preorder( aRootPtr->getLeftChild() );
    }

    if( aRootPtr->getRightChild() )
    {
        preorder( aRootPtr->getRightChild() );
    }
}

void BinarySearchTree::inorder()
{
    if( mRoot )
    {
        inorder( mRoot );
    }
    else
    {
        std::cout << "Nothing to print, the tree is empty.";
    }
}

void BinarySearchTree::inorder( Node* aRootPtr )
{
    if( aRootPtr->getLeftChild() )
    {
        inorder( aRootPtr->getLeftChild() );
    }

    std::cout << aRootPtr->getValue() << " ";

    if( aRootPtr->getRightChild() )
    {
        inorder( aRootPtr->getRightChild() );
    }
}

void BinarySearchTree::levelorder()
{
    Queue<Node*> levelOrderQ;

    if( mRoot )
    {
        levelOrderQ.enqueue( mRoot );
        levelorder( levelOrderQ );
    }
    else
    {
        std::cout << "Nothing to print, the tree is empty.";
    }
}

void BinarySearchTree::levelorder( Queue<Node*>& aLevelOrderQ )
{
    // Use the algorithm provided by the lab instructions to create the levelorder output
    Node* currentNodePtr = nullptr;

    if( !aLevelOrderQ.isEmpty() )
    {
        currentNodePtr = aLevelOrderQ.peekFront();

        if( currentNodePtr->getLeftChild() )
        {
            aLevelOrderQ.enqueue( currentNodePtr->getLeftChild() );
        }

        if( currentNodePtr->getRightChild() )
        {
            aLevelOrderQ.enqueue( currentNodePtr->getRightChild() );
        }

        std::cout << currentNodePtr->getValue() << " ";
        aLevelOrderQ.dequeue();

        levelorder( aLevelOrderQ );
    }
}

void BinarySearchTree::postOrderDelete( Node* aRootPtr )
{
    if( aRootPtr->getLeftChild() )
    {
        postOrderDelete( aRootPtr->getLeftChild() );
    }

    if( aRootPtr->getRightChild() )
    {
        postOrderDelete( aRootPtr->getRightChild() );
    }

    delete aRootPtr;
}
