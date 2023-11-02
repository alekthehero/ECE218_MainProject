#pragma once
#include <string>

class Person
{
public:
    Person();
    Person(int ssn, int day_Of_Birth, int month_Of_Birth, int year_Of_Birth, std::string first_name, std::string last_name, int code);
    ~Person();

    // Getters
    int getSSN();
    int getDayOfBirth();
    int getMonthOfBirth();
    int getYearOfBirth();
    std::string getFirstName();
    std::string getLastName();
    int getCode();

    // Setters
    void setSSN(int ssn);
    void setDayOfBirth(int day_Of_Birth);
    void setMonthOfBirth(int month_Of_Birth);
    void setYearOfBirth(int year_Of_Birth);
    void setFirstName(std::string first_name);
    void setLastName(std::string last_name);
    void setCode(int code);
    

protected:
    int ssn_;
    int day_Of_Birth_;
    int month_Of_Birth_;
    int year_Of_Birth_;
    std::string first_name_;
    std::string last_name_;
    int code_;
};
