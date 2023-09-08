#pragma once
#include <string>
#include <vector>
#include "../VariableStruc/Variable.h"

struct variable;

class RPN
{
public:
    RPN();
    ~RPN();

    void print() const;
    void print_variables() const;
    
    void perform_operation(char input) const;
    bool perform_function(const std::string& input) const;
    double back() const;
    void push(double input);
    void iterate_string(const std::string &input);
    bool two_items_check() const;

protected:
    std::vector<double> &rpn_stack_;
    std::vector<variable> variables_;
    
    
};
