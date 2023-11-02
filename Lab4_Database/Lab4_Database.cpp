#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "Person.h"

using namespace std;

int main(int argc, char* argv[])
{
    vector<Person*> people;

    ifstream database("database-million.txt");
    if(!database.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
    }


    string line;
    int ssn, day_Of_Birth, month_Of_Birth, year_Of_Birth, code;
    std::string first_name, last_name;
    
    while(getline(database, line))
    {
        istringstream iss(line);
        if(iss >> ssn >> day_Of_Birth >> month_Of_Birth >> year_Of_Birth >> first_name >> last_name >> code)
        {
            Person* person = new Person(ssn, day_Of_Birth, month_Of_Birth, year_Of_Birth, first_name, last_name, code);
            people.push_back(person);
            cout << "SSN: " << person->getSSN() << endl;
        }
    }

    cout << "Number of people: " << people.size() << endl;
    
    database.close();
    return 0;
}
