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
    Person* searchHelper(Node* root, std::string first, std::string last);
    void printByZipHelper(const Node* root, std::string zip);
    Person* searchOldestHelper(const Node* root, Person* oldestPerson);
    void saveHelper(Node* root, std::ofstream& file);

public:
    BinaryTree();
    ~BinaryTree();

    void insert(Person* data);
    void remove(Person* data);
    Person* search(std::string first, std::string last);
    Person* searchOldest();
    void relocatePerson(std::string first, std::string last, std::string newZip);
    
    void inOrderTraversal(Node* root);

    void save(std::string filename);

    void print();
    void printByZip(std::string zip);
    
};
