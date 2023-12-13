#include "BinaryTree.h"

#include <iostream>

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

    //Otherwise, find the correct place to insert the data based on data comparison
    Node* current = root;

    while (true)
    {
        // Compare data to decide whether to move left or right
        if (*data < *(current->data))
        {
            // Move left
            if (current->left == nullptr)
            {
                // If the left child is null, insert the new node here
                current->left = new Node(data);
                return;
            }
            // Move to the left child
            current = current->left;
        }
        else if (*(current->data) < *data)
        {
            // Move right
            if (current->right == nullptr)
            {
                // If the right child is null, insert the new node here
                current->right = new Node(data);
                return;
            }
            // Move to the right child
            current = current->right;
        }
        else
        {
            // In this example, I'm assuming duplicate names are not allowed, so we don't insert duplicates.
            return;
        }
    }
}

void BinaryTree::remove(Person* data)
{
}

Person* BinaryTree::search(std::string first, std::string last)
{
    return nullptr;
}

void BinaryTree::inOrderTraversal(Node* root) {
    if (root != nullptr) {
        inOrderTraversal(root->left);
        std::cout << root->data->first << " " << root->data->last << std::endl;
        inOrderTraversal(root->right);
    }
}

void BinaryTree::print()
{
    inOrderTraversal(root);
}
