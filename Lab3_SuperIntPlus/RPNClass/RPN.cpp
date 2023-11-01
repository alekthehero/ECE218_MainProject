#include "RPN.h"
#include <iostream>
#include <cctype>
#include <complex>

using namespace std;

RPN::~RPN()
{
    delete &rpn_stack_;
}

RPN::RPN(): rpn_stack_(*new std::vector<SuperInt>()), variables_(std::vector<variable>())
{
    //initialize the stack
    this->rpn_stack_ = std::vector<SuperInt>();
    this->variables_ = std::vector<variable>();
}

void RPN::print() const
{
    std::cout << "RPN Stack: ";
    for (const SuperInt i : this->rpn_stack_)
    {
        i.print(std::cout);
    }
    std::cout << std::endl;
}

void RPN::print_variables() const
{
    std::cout << "Variables: ";
    for (const variable &i : this->variables_)
    {
        i.print();
    }
    std::cout << std::endl;
    
}

SuperInt RPN::back() const
{
    if(this->rpn_stack_.empty())
    {
        cout << "\nError: Stack is empty" << endl;
        return SuperInt();
    }
    return this->rpn_stack_.back();
}

void RPN::push(const SuperInt input)
{
    this->rpn_stack_.push_back(input);
}

void RPN::iterate_string(const std::string& input)
{
    std::istringstream ss(input);
    
    // for testing
    if (input == "stack")
    {
        this->print();
        return;
    }
    if (input == "variables")
    {
        this->print_variables();
        return;
    }
    
    string accumulated_number;
    string accumulated_string;
    bool is_variable = false;
    bool is_negative = false;

    
    while(!ss.eof())
    {
        char curr_Char;
    
        ss.get(curr_Char);
        if (ss.eof())
        {
            if (is_variable)
            {
                cout << "Defining Variable: " << accumulated_string << endl;
                this->variables_.push_back(variable(accumulated_string, this->back())); // NOLINT(modernize-use-emplace)
                return;
            }

            if(!accumulated_string.empty())
            {
                perform_function(accumulated_string);
                accumulated_string.clear();
            }
            break;
        }
        
        if (isdigit(curr_Char))
        {
            accumulated_number += curr_Char;
        }
        else if (curr_Char == ' ')
        {
         
             if (!accumulated_number.empty()) {
           
                 this->push(SuperInt(accumulated_number, is_negative));
                 accumulated_number.clear();
                 is_negative = false;
             }
             
             if (!accumulated_string.empty())
             {
                 
                 if (is_variable)
                 {
                     cout << "\nDefining Variable: " << accumulated_string << endl;
                     this->variables_.push_back(variable(accumulated_string, this->back())); // NOLINT(modernize-use-emplace)
                     break;
                 }
                 
                 if(accumulated_string == "gcd" || accumulated_string == "random" || accumulated_string == "powmod")
                 {
                     perform_function(accumulated_string);
                     continue;
                 }
    
               
                 bool found = false;
                 for (const variable &var : this->variables_)
                 {
                     if (var.get_name() == accumulated_string)
                     {
                         //if the variable is in the vector then push the value onto the stack
                         this->push(var.get_value());
                         found = true;
                         break;
                     }
                 }
                 
                 if (!found)
                 {
                     cout << "Error: Variable " << accumulated_string << " not found" << endl;
                     return;
                 }
                 
                 accumulated_string.clear();
             }
        }
        else if (curr_Char == '=')
        {
            
            if (this->rpn_stack_.empty() || !accumulated_string.empty())
            {
                cout << "Error: Cannot define variable | Check formatting" << endl;
                break;
            }
            is_variable = true;
        }
        else if (isalpha(curr_Char))
        {
            accumulated_string += curr_Char;
        }
        else
        {
            const char next_char = ss.peek();
            if(next_char == ' ' || next_char == -1)
            {
                this->perform_operation(curr_Char);
            }
            else
            {
                // Set the negative flag
                is_negative = true;
            }
           
        }
        
    }
    
    cout << "Result: ";
    this->back().printf(std::cout);
    this->rpn_stack_.clear();
    accumulated_string.clear();
    accumulated_number.clear();
}

bool RPN::two_items_check() const
{
    // if the stack doesnt contain at least 2 items then we cant do an operation
    if (this->rpn_stack_.size() < 2)
    {
        cout << "Error: Not enough items in the stack to perform an operation\nPlease enter valid input! | Add Spaces!!" << endl;
        return false;
    }
    return true;
}

void RPN::perform_operation(const char input) const
{
    
    if(input == '+')
    {
        //addition
        if(!this->two_items_check())
        {
            return;
        }
        SuperInt num1 = this->back();
        this->rpn_stack_.pop_back();
        const SuperInt num2 = this->back();
        this->rpn_stack_.pop_back();
        this->rpn_stack_.push_back(num1 + num2);
    }
    else if(input == '-')
    {
        //subtraction
        if(!this->two_items_check())
        {
            return;
        }
        const SuperInt num1 = this->back();
        this->rpn_stack_.pop_back();
        SuperInt num2 = this->back();
        this->rpn_stack_.pop_back();
        this->rpn_stack_.push_back(num2 - num1);
    }
    else if(input == '*')
    {
        //multiplication
        if(!this->two_items_check())
        {
            return;
        }
        SuperInt num1 = this->back();
        this->rpn_stack_.pop_back();
        SuperInt num2 = this->back();
        this->rpn_stack_.pop_back();
        this->rpn_stack_.push_back(num1 * num2);
    }
    else if(input == '!')
    {
        //factorial
        SuperInt num1 = this->back();
        this->rpn_stack_.push_back(num1.factorial(num1.get_int()));
    }
    else if(input == '/')
    {
        //division
        if(!this->two_items_check())
        {
            return;
        }
        SuperInt num1 = this->back();
        this->rpn_stack_.pop_back();
        SuperInt num2 = this->back();
        this->rpn_stack_.pop_back();
        this->rpn_stack_.push_back(num2 / num1);
    }
    else if(input == '^')
    {
        //exponentiation
        if(!this->two_items_check())
        {
            return;
        }
        SuperInt num1 = this->back();
        this->rpn_stack_.pop_back();
        SuperInt num2 = this->back();
        this->rpn_stack_.pop_back();
        this->rpn_stack_.push_back(num2 ^ num1);
    }
    else if(input == '%')
    {
        //modulus
        if(!this->two_items_check())
        {
            return;
        }
        SuperInt num1 = this->back();
        this->rpn_stack_.pop_back();
        SuperInt num2 = this->back();
        this->rpn_stack_.pop_back();
        this->rpn_stack_.push_back(num2 % num1);
    }
    else
    {
        cout << "\nError Finding Operator: " << input << endl;
    }
}

void RPN::perform_function(std::string input) const
{
    if (input == "gcd")
    {
        //GCD
        if(!this->two_items_check())
        {
            return;
        }
        SuperInt num1 = this->back();
        this->rpn_stack_.pop_back();
        SuperInt num2 = this->back();
        this->rpn_stack_.pop_back();
        this->rpn_stack_.push_back(SuperInt::gcd(num1, num2));
    }
    else if (input == "random")
    {
        //Random
        if(!this->two_items_check())
        {
            return;
        }
        SuperInt num1 = this->back();
        this->rpn_stack_.pop_back();
        SuperInt num2 = this->back();
        this->rpn_stack_.pop_back();
        this->rpn_stack_.push_back(num1.random(num2.get_int(), num1.get_int()));
    }
    else if (input == "powmod")
    {
        //PowMod
        if (this->rpn_stack_.size() < 3)
        {
            cout << "Error: Not enough items in the stack to perform an operation\nPlease enter valid input! | Add Spaces!!" << endl;
            return;
        }
        SuperInt num1 = this->back();
        this->rpn_stack_.pop_back();
        SuperInt num2 = this->back();
        this->rpn_stack_.pop_back();
        SuperInt num3 = this->back();
        this->rpn_stack_.pop_back();
        this->rpn_stack_.push_back(num3.powmod(num2, num1));
    }
}


