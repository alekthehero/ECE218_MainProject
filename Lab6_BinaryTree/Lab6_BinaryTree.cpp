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
    int count = 0;
    while (true)
    {
        std::string firstName, lastName, zip;
        int social, birthDay, birthMonth, birthYear;
        file >> social >> birthDay >> birthMonth >> birthYear >> firstName >> lastName >> zip;
        int birthDate = birthYear * 10000 + birthMonth * 100 + birthDay;
        Person* person = new Person(social, birthDate, firstName, lastName, zip);
        
        tree.insert(person);
        count++;

        if (file.eof()) {
            break;
        }
    }

    file.close();
    std::cout << "Loaded " << count << " records." << std::endl;
    
    while (true) {
        std::cout << "Enter command (FIND, PRINT, ZIP, OLDEST, SAVE, RELOCATE, EXIT): ";
        std::string command;
        std::cin >> command;

        if (command == "FIND") {
            std::string findFirstName, findLastName;
            std::cin >> findFirstName >> findLastName;
            Person* person = tree.search(findFirstName, findLastName);
            if (person != nullptr) {
                std::cout << "Found " << person->first << " " << person->last << " " << person->birthDate << " " << person->social << " " << person->zip << std::endl;
            } else {
                std::cout << "Person not found" << std::endl;
            }
        } else if (command == "PRINT") {
            tree.print();
        } else if (command == "ZIP") {
            std::string zipCode;
            std::cin >> zipCode;
            tree.printByZip(zipCode);
            
        } else if (command == "OLDEST") {
            Person* oldest = tree.searchOldest();
            if (oldest != nullptr) {
                std::cout << "Oldest person is " << oldest->first << " " << oldest->last << " " << oldest->birthDate << " " << oldest->social << " " << oldest->zip << std::endl;
            } else {
                std::cout << "No people in tree" << std::endl;
            }
            
        } else if (command == "SAVE") {
            std::string saveFilename;
            std::cin >> saveFilename;

            tree.save(saveFilename);
            
        } else if (command == "RELOCATE") {
            std::string relocateFirstName, relocateLastName, newZipCode;
            std::cin >> relocateFirstName >> relocateLastName >> newZipCode;

            tree.relocatePerson(relocateFirstName, relocateLastName, newZipCode);
            
        } else if (command == "EXIT") {
            break;
        } else {
            std::cout << "Invalid command. Try again." << std::endl;
        }
    }

    
    return 0;
}
