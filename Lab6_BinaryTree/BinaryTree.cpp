#include "BinaryTree.h"

BinaryTree::BinaryTree()
{
    root = nullptr;
}

BinaryTree::~BinaryTree()
{
    delete root;
}

void BinaryTree::insert(Person* data)
{
    //Insert data into the tree
    //If the tree is empty, set the root to the new node
    if (root == nullptr)
    {
        root = new Node(data);
        return;
    }

    //Otherwise, find the correct place to insert the data
    Node* current = root;
    
}

void BinaryTree::remove(Person* data)
{
}

Person* BinaryTree::search(std::string first, std::string last)
{
}
