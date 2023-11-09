#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>
#include <time.h>
#include "Person.h"

using namespace std;

int partition(vector<person*>& people, int left, int right)
{
    person* pivot_value = people[right];
    int i = left;

    for (int j = left; j < right; j++)
    {
        if (people[j]->get_last_name() < pivot_value->get_last_name())
        {
            swap(people[i], people[j]);
            i++;
        }
        else if (people[j]->get_last_name() == pivot_value->get_last_name())
        {
            if (people[j]->get_first_name() < pivot_value->get_first_name())
            {
                swap(people[i], people[j]);
                i++;
            }
            else if (people[j]->get_first_name() == pivot_value->get_first_name())
            {
                if (people[j]->get_ssn() < pivot_value->get_ssn())
                {
                    swap(people[i], people[j]);
                    i++;
                }
            }
        }
    }

    swap(people[i], people[right]);

    return i;
}

void quick_sort(vector<person*>& people, int left, int right)
{
    if (left < right)
    {
        int pivot_index = partition(people, left, right);

        quick_sort(people, left, pivot_index - 1);
        quick_sort(people, pivot_index + 1, right);
    }
}

int main(int argc, char* argv[])
{
    vector<person*> people;

    ifstream database("database-million.txt");
    if(!database.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
    }
    
    int ssn, day_of_birth, month_of_birth, year_of_birth;
    std::string first_name, last_name, code;

    cout << "Reading from file..." << endl;
    
    while(database >> ssn >> day_of_birth >> month_of_birth >> year_of_birth >> first_name >> last_name >> code)
    {
        person* p = new person(ssn, day_of_birth, month_of_birth, year_of_birth, first_name, last_name, code);
        people.push_back(p);
    }

    cout << "\nNumber of people: " << people.size() << endl << endl;
    
    database.close();

    double before = clock();
    
    quick_sort(people, 0, people.size() - 1);

    double after = clock();

    cout << "Time to sort: " << (after - before) / CLOCKS_PER_SEC << " seconds" << endl;

    cout << "Writing to file..." << endl;
    
    ofstream sorted("sorted.txt");
    if(!sorted.is_open()) {
        cout << "Error opening file" << endl;
        return 1;
    }

    for (person*& i : people)
    {
        sorted << setw(9) << setfill('0') << i->get_ssn() << " " <<
            setw(2) << setfill('0') << i->get_day_of_birth() << " " <<
            setw(2) << setfill('0') << i->get_month_of_birth() << " " <<
            setw(2) << setfill('0') << i->get_year_of_birth() << " " <<
            i->get_first_name() << " " << i->get_last_name() << " " << i->get_code() << endl;
    }

    sorted.close();

    cout << "\n\nDone!" << endl;
    cout << "Time to sort: " << (after - before) / CLOCKS_PER_SEC << " seconds" << endl;
    
    return 0;
}
