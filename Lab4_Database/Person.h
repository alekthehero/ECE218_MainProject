#pragma once
#include <string>

class person
{
public:
    person();
    person(int ssn, int day_of_birth, int month_of_birth, int year_of_birth, const std::string& first_name, const std::string& last_name, int code);
    ~person();

    // Getters
    int get_ssn() const;
    int get_day_of_birth() const;
    int get_month_of_birth() const;
    int get_year_of_birth() const;
    std::string get_first_name();
    std::string get_last_name();
    int get_code() const;

    // Setters
    void set_ssn(int ssn);
    void set_day_of_birth(int day_of_birth);
    void set_month_of_birth(int month_of_birth);
    void set_year_of_birth(int year_of_birth);
    void set_first_name(const std::string& first_name);
    void set_last_name(const std::string& last_name);
    void set_code(int code);
    

protected:
    int ssn_;
    int day_Of_Birth_;
    int month_Of_Birth_;
    int year_Of_Birth_;
    std::string first_name_;
    std::string last_name_;
    int code_;
};
