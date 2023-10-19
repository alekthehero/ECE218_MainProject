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
    //print out just the rpn stack
    std::cout << "RPN Stack: ";
    for (const SuperInt i : this->rpn_stack_)
    {
        i.print(std::cout);
    }
    std::cout << std::endl;
}

void RPN::print_variables() const
{
    //print the variables vector
    std::cout << "Variables: ";
    for (const variable &i : this->variables_)
    {
        i.print();
    }
    std::cout << std::endl;
    
}

SuperInt RPN::back() const
{
    //check to make sure the stack is not empty
    if(this->rpn_stack_.empty())
    {
        //if the stack is empty then return 0
        cout << "\nError: Stack is empty" << endl;
        return SuperInt();
    }
    //return the last element in the stack
    return this->rpn_stack_.back();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void RPN::push(const SuperInt input)
{
    //push the input onto the stack
    this->rpn_stack_.push_back(input);
}

void RPN::iterate_string(const std::string& input)
{
    // coming in like 3 2 + 4 6 + +

    // Change input to stringstream for easier parsing
    std::stringstream ss(input);
    
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
    
    //iterate over the string if the character is a number add it to the stack if its an operator do the operation
    //if its a space then do nothing
    //if its a . then end the loop
    //if its a letter then check if its a variable or a function
    //if its a variable then check if its in the vector

    // Make sure user did not forget the period at end of input
    if (input.back() != '.')
    {
        cout << "\nError: Missing period at end of input" << endl;
        return;
    }
    
    string accumulated_number;
    string accumulated_string;
    bool is_variable = false;
    
    for (const char i : input)
    {
        //check if the character is a number
        if (isdigit(i))
        {
            //add the number to the stack
            accumulated_number += i;
        }
        else if (i == ' ')
        {
            //push the accumulated number onto the stack
            if (!accumulated_number.empty()) {
                // Convert the accumulated digits to a double and push onto the stack
                this->push(SuperInt(accumulated_number));
                accumulated_number.clear(); // Reset the digit accumulator
            }
            //check if the accumulated string is a variable
            if (!accumulated_string.empty())
            {
                //if its not a function then check if we are defining it now
                if (is_variable)
                {
                    cout << "\nDefining Variable: " << accumulated_string << endl;
                    this->variables_.push_back(variable(accumulated_string, this->back())); // NOLINT(modernize-use-emplace)
                    break;
                }

                //check if the variable is in the vector
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
                    cout << "\nWarn: Variable " << accumulated_string << " not found" << endl;
                    //prompt the user to enter it now
                    cout << "Enter the value for " << accumulated_string << ": ";
                    string value;
                    cin >> value;
                    //push the value onto the stack
                    this->push(SuperInt(value));
                    //add the variable to the vector
                    this->variables_.push_back(variable(accumulated_string, SuperInt(value)));  // NOLINT(modernize-use-emplace)
                    cin.ignore();
                }
                
                //clear the accumulated string
                accumulated_string.clear();
            }
        }
        else if (i == '.')
        {
            
            //print the last item on the stack
            cout << "\nResult: ";
            this->back().printf(std::cout);
            //clear the stack
            this->rpn_stack_.clear();
            //clear the accumulated string and number
            accumulated_string.clear();
            accumulated_number.clear();
            
            break;
        }
        else if (i == '=')
        {
            // if the stack is empty then we cant define a variable and if the accumulated string has contents the format is wrong
            if (this->rpn_stack_.empty() || !accumulated_string.empty())
            {
                cout << "\nError: Cannot define variable | Check formatting" << endl;
                break;
            }
            is_variable = true;
        }
        else if (isalpha(i))
        {
            //Accumulate the string
            accumulated_string += i;
        }
        else
        {
            
            //if there is an operator then we need to do the operation
            //do the calculation with the given operator
            this->perform_operation(i);
            
        }
    }
    
}

bool RPN::two_items_check() const
{
    // if the stack doesnt contain at least 2 items then we cant do an operation
    if (this->rpn_stack_.size() < 2)
    {
        cout << "\nError: Not enough items in the stack to perform an operation\nPlease enter valid input! | Add Spaces!!" << endl;
        return false;
    }
    return true;
}

/**
 * \brief Check the operator for the input character
 * \param input the single character input to check for an operation to occur
 */
void RPN::perform_operation(const char input) const
{
    
    //do a check for the operators depending on the input
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
    else
    {
        cout << "\nError Finding Operator: " << input << endl;
    }
}


