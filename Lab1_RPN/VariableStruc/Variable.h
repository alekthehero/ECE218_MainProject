#pragma once
#include <iostream>
#include <ostream>
#include <string>

struct variable
{
public:
    variable();
    variable(const std::string& name, double value);

    //getters
    std::string get_name() const { return this->name_; }
    double get_value() const { return this->value_; }

    //setters
    void set_name(const std::string& name);
    void set_value(const double value);

    //Print
    void print() const { std::cout << "\n" << this->name_ << " = " << this->value_ << std::endl; }

protected:
    std::string name_;
    double value_;
    
    
    
};
