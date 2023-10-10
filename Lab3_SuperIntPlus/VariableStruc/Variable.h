#pragma once
#include <iostream>
#include <ostream>
#include <string>
#include "../SuperInt/SuperInt.h"

struct variable
{
public:
    variable();
    variable(const std::string& name, SuperInt value);

    //getters
    std::string get_name() const { return this->name_; }
    SuperInt get_value() const { return this->value_; }

    //setters
    void set_name(const std::string& name);
    void set_value(const SuperInt value);

    //Print
    void print() const { std::cout << "\n" << this->name_ << " = " << this->value_.get_int() << std::endl; }

protected:
    std::string name_;
    SuperInt value_;
    
    
    
};
