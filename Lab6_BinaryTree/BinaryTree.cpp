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
    return searchHelper(root, first, last);
}

Person* BinaryTree::searchHelper(Node* root, std::string first, std::string last) {
    if (root == nullptr || (root->data->first == first && root->data->last == last)) {
        return (root != nullptr) ? root->data : nullptr;
    }

    if (last < root->data->last || (last == root->data->last && first < root->data->first)) {
        return searchHelper(root->left, first, last);
    } else {
        return searchHelper(root->right, first, last);
    }
}

void BinaryTree::inOrderTraversal(Node* root) {
    if (root != nullptr) {
        inOrderTraversal(root->left);
        std::cout << root->data->first << " " << root->data->last << " " << root->data->birthDate << " " << root->data->social << " " << root->data->zip << std::endl;
        inOrderTraversal(root->right);
    }
}

void BinaryTree::print()
{
    inOrderTraversal(root);
}

void BinaryTree::printByZip(std::string zip)
{
    printByZipHelper(root, zip);
}

void BinaryTree::printByZipHelper(const Node* root, std::string zip) {
    if (root != nullptr) {
        printByZipHelper(root->left, zip);

        // Check if the person's zip code matches the specified zip
        if (root->data->zip == zip) {
            // Print information about the person
            std::cout << root->data->last << ", " << root->data->first << std::endl;
            // Add other fields as needed
        }

        printByZipHelper(root->right, zip);
    }
}

Person* BinaryTree::searchOldestHelper(const Node* root, Person* oldestPerson)
{
    if (root != nullptr) {
        // Traverse the left subtree first
        oldestPerson = searchOldestHelper(root->left, oldestPerson);

        // Check if the current person is older than the currently known oldest person
        if (oldestPerson == nullptr || root->data->birthDate > oldestPerson->birthDate) {
            oldestPerson = root->data;
        }

        // Traverse the right subtree
        oldestPerson = searchOldestHelper(root->right, oldestPerson);
    }

    return oldestPerson;
}

Person* BinaryTree::searchOldest()
{
    return searchOldestHelper(root, nullptr);
}
