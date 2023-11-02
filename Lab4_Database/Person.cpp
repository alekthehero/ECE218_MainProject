#include "Person.h"

Person::Person()
{
    this->ssn_ = 0;
    this->day_Of_Birth_ = 0;
    this->month_Of_Birth_ = 0;
    this->year_Of_Birth_ = 0;
    this->first_name_ = "";
    this->last_name_ = "";
    this->code_ = 0;
}

Person::Person(int ssn, int day_Of_Birth, int month_Of_Birth, int year_Of_Birth, std::string first_name,
    std::string last_name, int code)
{
    this->ssn_ = ssn;
    this->day_Of_Birth_ = day_Of_Birth;
    this->month_Of_Birth_ = month_Of_Birth;
    this->year_Of_Birth_ = year_Of_Birth;
    this->first_name_ = first_name;
    this->last_name_ = last_name;
    this->code_ = code;
}

Person::~Person()
{
    
}

int Person::getSSN()
{
    return this->ssn_;
}

int Person::getDayOfBirth()
{
    return this->day_Of_Birth_;
}

int Person::getMonthOfBirth()
{
    return this->month_Of_Birth_;
}

int Person::getYearOfBirth()
{
    return this->year_Of_Birth_;
}

std::string Person::getFirstName()
{
    return this->first_name_;
}

std::string Person::getLastName()
{
    return this->last_name_;
}

int Person::getCode()
{
    return this->code_;
}

void Person::setSSN(int ssn)
{
    this->ssn_ = ssn;
}

void Person::setDayOfBirth(int day_Of_Birth)
{
    this->day_Of_Birth_ = day_Of_Birth;
}

void Person::setMonthOfBirth(int month_Of_Birth)
{
    this->month_Of_Birth_ = month_Of_Birth;
}

void Person::setYearOfBirth(int year_Of_Birth)
{
    this->year_Of_Birth_ = year_Of_Birth_;
}

void Person::setFirstName(std::string first_name)
{
    this->first_name_ = first_name_;
}

void Person::setLastName(std::string last_name)
{
    this->last_name_ = last_name_;
}

void Person::setCode(int code)
{
    this->code_ = code;
}
