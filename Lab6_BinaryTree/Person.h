#pragma once
#include <string>

struct Person
{
    int social, birthDate;
    std::string first, last, zip;

    Person() : social(0), birthDate(0), first(""), last(""), zip("") {}
    Person(int social, int birthDate, std::string first, std::string last, std::string zip) : social(social), birthDate(birthDate), first(first), last(last), zip(zip) {}
    Person(const Person& other) : social(other.social), birthDate(other.birthDate), first(other.first), last(other.last), zip(other.zip) {}
    Person& operator=(const Person& other)
    {
        if (this != &other)
        {
            social = other.social;
            birthDate = other.birthDate;
            first = other.first;
            last = other.last;
            zip = other.zip;
        }
        return *this;
    }
    bool operator==(const Person& other) const
    {
        //Compare last name then first name
        return last == other.last && first == other.first;
    }
    bool operator!=(const Person& other) const
    {
        return !(*this == other);
    }
    bool operator<(const Person& other) const
    {
        //Compare last name then first name
        if (last < other.last)
            return true;
        if (last == other.last)
            return first < other.first;
        return false;
    }
    bool operator>(const Person& other) const
    {
        //Compare last name then first name
        if (last > other.last)
            return true;
        if (last == other.last)
            return first > other.first;
        return false;
    }
    bool operator<=(const Person& other) const
    {
        return !(*this > other);
    }
    bool operator>=(const Person& other) const
    {
        return !(*this < other);
    }
};
