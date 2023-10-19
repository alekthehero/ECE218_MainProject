#pragma once
#include <string>
#include <vector>
#include "../VariableStruc/Variable.h"
#include "../SuperInt/SuperInt.h"

struct variable;

class RPN
{
public:
    RPN();
    ~RPN();

    void print() const;
    void print_variables() const;
    
    void perform_operation(char input) const;
    SuperInt back() const;
    void push(const SuperInt& input);
    void iterate_string(const std::string &input);
    bool two_items_check() const;

protected:
    std::vector<SuperInt> &rpn_stack_;
    std::vector<variable> variables_;
    
    
};
