#include <fstream>
#include <iostream>

#include "BinaryTree.h"
#include "Person.h"

int main(int argc, char* argv[]) {
    // Check if the correct number of command line arguments is provided
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;  // Exit with an error code
    }

    // Get the filename from the command line arguments
    const std::string filename = argv[1];

    // Open the file
    std::fstream file(filename, std::ios::in);

    // Check if the file is successfully opened
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return 1;  // Exit with an error code
    }

    BinaryTree tree;

    //Read a line of the file, turn it into a person object, and insert it into the binary tree
    while (!file.eof())
    {
        std::string firstName, lastName, zip;
        int social, birthDate;
        file >> social >> birthDate >> firstName >> lastName >> zip;
        Person* person = new Person(social, birthDate, firstName, lastName, zip);

        tree.insert(person);
        std::cout << "Inserted " << firstName << " " << lastName << std::endl;
    }

    file.close();

    tree.print();
    
    return 0;  // Exit successfully
}
