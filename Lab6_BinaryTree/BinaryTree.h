#pragma once
#include "Person.h"

struct Node
{
    Person* data;
    Node* left;
    Node* right;

    Node() : data(nullptr), left(nullptr), right(nullptr) {}
    Node(Person* data) : data(data), left(nullptr), right(nullptr) {}
    Node(Person* data, Node* left, Node* right) : data(data), left(left), right(right) {}
    
};

class BinaryTree
{
protected:
    Node* root;

public:
    BinaryTree();
    ~BinaryTree();

    void insert(Person* data);
    void remove(Person* data);
    Person* search(std::string first, std::string last);
    void inOrderTraversal(Node* root);

    void print();
};
