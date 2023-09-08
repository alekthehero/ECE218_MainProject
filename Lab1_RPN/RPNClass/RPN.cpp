#include "RPN.h"
#include <iostream>
#include <cctype>

using namespace std;

RPN::~RPN()
{
    delete &rpn_stack_;
}

RPN::RPN(): rpn_stack_(*new std::vector<double>()), variables_(std::vector<variable>())
{
    //initialize the stack
    this->rpn_stack_ = std::vector<double>();
    this->variables_ = std::vector<variable>();
}

void RPN::print() const
{
    //print out just the rpn stack
    std::cout << "RPN Stack: ";
    for (const double i : this->rpn_stack_)
    {
        std::cout << i << " ";
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

double RPN::back() const
{
    //check to make sure the stack is not empty
    if(this->rpn_stack_.empty())
    {
        //if the stack is empty then return 0
        cout << "\nError: Stack is empty" << endl;
        return NULL;
    }
    //return the last element in the stack
    return this->rpn_stack_.back();
}

// ReSharper disable once CppMemberFunctionMayBeConst
void RPN::push(const double input)
{
    //push the input onto the stack
    this->rpn_stack_.push_back(input);
}

void RPN::iterate_string(const std::string& input)
{
    // coming in like 3 2 + 4 6 + + .

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
                this->push(std::stod(accumulated_number));
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
                
                //Check if the accumulated string is a function
                if (this->perform_function(accumulated_string))
                {
                    //if it is a function then clear the accumulated string
                    accumulated_string.clear();
                    continue;
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
                    double value;
                    cin >> value;
                    //push the value onto the stack
                    this->push(value);
                    //add the variable to the vector
                    this->variables_.push_back(variable(accumulated_string, value));  // NOLINT(modernize-use-emplace)
                    cin.ignore();
                }
                
                //clear the accumulated string
                accumulated_string.clear();
            }
        }
        else if (i == '.')
        {
            
            //print the last item on the stack
            cout << "\nResult: " << this->back() << endl;
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
            
            //for testing print the stack contents
            this->print();
            
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
        const double num1 = this->back();
        this->rpn_stack_.pop_back();
        const double num2 = this->back();
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
        const double num1 = this->back();
        this->rpn_stack_.pop_back();
        const double num2 = this->back();
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
        const double num1 = this->back();
        this->rpn_stack_.pop_back();
        const double num2 = this->back();
        this->rpn_stack_.pop_back();
        this->rpn_stack_.push_back(num1 * num2);
    }
    else if(input == '/')
    {
        //division
        if(!this->two_items_check())
        {
            return;
        }
        const double num1 = this->back();
        if (num1 == 0.0)
        {
            cout << "\nError: Cannot divide by 0" << endl;
            return;
        }
        this->rpn_stack_.pop_back();
        const double num2 = this->back();
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
        const double num1 = this->back();
        this->rpn_stack_.pop_back();
        const double num2 = this->back();
        this->rpn_stack_.pop_back();
        this->rpn_stack_.push_back(pow(num2, num1));
    }
    else if(input == '!')
    {
        //factorial
        const double num1 = this->back();
        this->rpn_stack_.pop_back();
        double factorial = 1;
        for(int i = 1; i <= num1; i++)
        {
            factorial *= i;
        }
        this->rpn_stack_.push_back(factorial);
    }
    else
    {
        cout << "\nError Finding Operator: " << input << endl;
    }
    cout << "Operator: " << input << " | Result: " << this->back() << endl;
}

bool RPN::perform_function(const std::string& input) const
{
    //check if the input is a function
    if(input == "sin")
    {
        //sine
        const double num1 = this->back();
        this->rpn_stack_.pop_back();
        this->rpn_stack_.push_back(sin(num1));
        this->print();
        return true;
    }
    if(input == "cos")
    {
        //cosine
        const double num1 = this->back();
        this->rpn_stack_.pop_back();
        this->rpn_stack_.push_back(cos(num1));
        return true;
    }
    if(input == "tan")
    {
        //tangent
        const double num1 = this->back();
        this->rpn_stack_.pop_back();
        this->rpn_stack_.push_back(tan(num1));
        return true;
    }
    if(input == "asin")
    {
        //arcsine
        const double num1 = this->back();
        this->rpn_stack_.pop_back();
        this->rpn_stack_.push_back(asin(num1));
        return true;
    }
    if(input == "acos")
    {
        //arccosine
        const double num1 = this->back();
        this->rpn_stack_.pop_back();
        this->rpn_stack_.push_back(acos(num1));
        return true;
    }
    if(input == "atan")
    {
        //arctangent
        const double num1 = this->back();
        this->rpn_stack_.pop_back();
        this->rpn_stack_.push_back(atan(num1));
        return true;
    }
    if(input == "sqrt")
    {
        //square root
        const double num1 = this->back();
        this->rpn_stack_.pop_back();
        this->rpn_stack_.push_back(sqrt(num1));
        return true;
    }
    if(input == "log")
    {
        //log base 10
        const double num1 = this->back();
        this->rpn_stack_.pop_back();
        this->rpn_stack_.push_back(log10(num1));
        return true;
    }
    if(input == "ln")
    {
        //natural log
        const double num1 = this->back();
        this->rpn_stack_.pop_back();
        this->rpn_stack_.push_back(log(num1));
        return true;
    }
    if(input == "abs")
    {
        //absolute value
        const double num1 = this->back();
        this->rpn_stack_.pop_back();
        this->rpn_stack_.push_back(abs(num1));
        return true;
    }
    
    cout << "\nNo Function: " << input << " | Checking for variables" << endl;
    return false;
}


