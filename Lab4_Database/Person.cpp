#include "Person.h"

person::person()
{
    this->ssn_ = 0;
    this->day_Of_Birth_ = 0;
    this->month_Of_Birth_ = 0;
    this->year_Of_Birth_ = 0;
    this->first_name_ = "";
    this->last_name_ = "";
    this->code_ = 0;
}

person::person(const int ssn, const int day_of_birth, const int month_of_birth, const int year_of_birth,
    const std::string& first_name,
    const std::string& last_name,
    const int code)
{
    this->ssn_ = ssn;
    this->day_Of_Birth_ = day_of_birth;
    this->month_Of_Birth_ = month_of_birth;
    this->year_Of_Birth_ = year_of_birth;
    this->first_name_ = first_name;
    this->last_name_ = last_name;
    this->code_ = code;
}

person::~person() = default;

int person::get_ssn() const
{
    return this->ssn_;
}

int person::get_day_of_birth() const
{
    return this->day_Of_Birth_;
}

int person::get_month_of_birth() const
{
    return this->month_Of_Birth_;
}

int person::get_year_of_birth() const
{
    return this->year_Of_Birth_;
}

std::string person::get_first_name()
{
    return this->first_name_;
}

std::string person::get_last_name()
{
    return this->last_name_;
}

int person::get_code() const
{
    return this->code_;
}

void person::set_ssn(const int ssn)
{
    this->ssn_ = ssn;
}

void person::set_day_of_birth(const int day_of_birth)
{
    this->day_Of_Birth_ = day_of_birth;
}

void person::set_month_of_birth(const int month_of_birth)
{
    this->month_Of_Birth_ = month_of_birth;
}

void person::set_year_of_birth(const int year_of_birth)
{
    this->year_Of_Birth_ = year_of_birth;
}

void person::set_first_name(const std::string& first_name)
{
    this->first_name_ = first_name;
}

void person::set_last_name(const std::string& last_name)
{
    this->last_name_ = last_name;
}

void person::set_code(const int code)
{
    this->code_ = code;
}
