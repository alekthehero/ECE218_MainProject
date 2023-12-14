#include "BinaryTree.h"
#include <fstream>
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
    if (root == nullptr)
    {
        root = new Node(data);
        return;
    }
    
    Node* current = root;

    while (true)
    {
        if (*data < *(current->data))
        {
            if (current->left == nullptr)
            {
                current->left = new Node(data);
                return;
            }
            current = current->left;
        }
        else if (*(current->data) < *data)
        {
            if (current->right == nullptr)
            {
                
                current->right = new Node(data);
                return;
            }
            current = current->right;
        }
        else
        {
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

void BinaryTree::save(std::string filename)
{
    std::ofstream outFile(filename);

    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for writing." << std::endl;
        return;
    }
    saveHelper(root, outFile);
    outFile.close();

    std::cout << "Saved to " << filename << std::endl;
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
        oldestPerson = searchOldestHelper(root->left, oldestPerson);
        
        if (oldestPerson == nullptr || root->data->birthDate > oldestPerson->birthDate) {
            oldestPerson = root->data;
        }
        
        oldestPerson = searchOldestHelper(root->right, oldestPerson);
    }

    return oldestPerson;
}

void BinaryTree::saveHelper(const Node* root, std::ofstream& file)
{
    if (root != nullptr) {
        saveHelper(root->left, file);
        file << root->data->social << " " << root->data->birthDate << " " << root->data->first << " " << root->data->last << " " << root->data->zip << std::endl;
        saveHelper(root->right, file);
    }
}

Person* BinaryTree::searchOldest()
{
    return searchOldestHelper(root, nullptr);
}

void BinaryTree::relocatePerson(std::string first, std::string last, std::string newZip)
{
    Person* person = search(first, last);
    if (person != nullptr) {
        person->zip = newZip;
        std::cout << "Relocated " << first << " " << last << " to " << newZip << std::endl;
    }
    else
    {
        std::cout << "No person found" << std::endl;
    }
}
