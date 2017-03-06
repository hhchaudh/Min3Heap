#include "Node.h"

Node::Node( int aValue ) :
    mValue(aValue),
    mLeftChildPtr(nullptr),
    mRightChildPtr(nullptr)
{
}

Node* Node::getLeftChild()
{
    return mLeftChildPtr;
}

Node* Node::getRightChild()
{
    return mRightChildPtr;
}

void Node::setLeftChild( Node* aNodePtr )
{
    mLeftChildPtr = aNodePtr;
}

void Node::setRightChild( Node* aNodePtr )
{
    mRightChildPtr = aNodePtr;
}

int Node::getValue() const
{
    return mValue;
}

void Node::setValue( int aValue )
{
    mValue = aValue;
}
