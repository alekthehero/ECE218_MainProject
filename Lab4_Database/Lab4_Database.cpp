#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "Person.h"

using namespace std;

int main(int argc, char* argv[])
{
    vector<person*> people;

    ifstream database("database-thousand.txt");
    if(!database.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
    }

    std::string line;
    int ssn, day_of_birth, month_of_birth, year_of_birth;
    std::string first_name, last_name, code;
    
    while(getline(database, line))
    {
        istringstream iss(line);
        iss >> ssn >> day_of_birth >> month_of_birth >> year_of_birth >> first_name >> last_name >> code;
        
        person* p = new person(ssn, day_of_birth, month_of_birth, year_of_birth, first_name, last_name, code);
        people.push_back(p);
        cout << "First Name: " << p->get_first_name() << endl;
    }

    cout << "Number of people: " << people.size() << endl;
    
    database.close();
    return 0;
}
