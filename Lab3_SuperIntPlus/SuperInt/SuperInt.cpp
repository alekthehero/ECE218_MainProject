#include "SuperInt.h"

#include <iostream>
#include <ostream>
#include <limits>

SuperInt::SuperInt()
{
    //Default constructor
    digits_ = std::vector<int>();   
}

SuperInt::SuperInt(const SuperInt& other)
{
    //Constructor when we have a SuperInt object
    digits_ = other.digits_;
}

SuperInt::SuperInt(const std::string& str)
{
    digits_ = std::vector<int>();
    for (const char digit_char : str) {
        if (isdigit(digit_char)) {
            digits_.push_back(digit_char - '0');
        }
        else
        {
            
        }
    }
}

SuperInt::~SuperInt()
{
    //delete &digits_;
}

void SuperInt::print(std::ostream& out) const
{
    for (const int digit : digits_) {
        out << std::to_string(digit);
    }
}

std::ostream& SuperInt::operator<<(std::ostream& out) const
{
    for (const int digit : digits_) {
        out << std::to_string(digit);
    }
    return out;
}

void SuperInt::printf(std::ostream& out) const
{
    int char_count = 0;

    for (const int digit : digits_) {
        out << std::to_string(digit);
        char_count++;

        // new line every 50
        if (char_count % 50 == 0 && char_count < digits_.size()) {
            out << "\n";
        }
    }
}

SuperInt SuperInt::operator+(const SuperInt& other)
{
    SuperInt result;

    // carry and index
    int carry = 0;
    int i = digits_.size() - 1;
    int j = other.digits_.size() - 1;

    // add right to left
    while (i >= 0 || j >= 0 || carry) {
        // sum is equal to the carry from the last iteration
        int sum = carry;
        // check if we have digits left to add
        if (i >= 0) {
            sum += digits_[i];
            i--;
        }
        if (j >= 0) {
            sum += other.digits_[j];
            j--;
        }

        // calculate the carry and sum
        carry = sum / 10;
        sum %= 10;

        // add the digit to the result
        result.digits_.insert(result.digits_.begin(), sum);
    }

    return result;
}

SuperInt SuperInt::operator-(const SuperInt& other)
{
    SuperInt result;

    // Borrow and index
    int borrow = 0;
    int i = digits_.size() - 1;
    int j = other.digits_.size() - 1;

    // Subtract right to left
    while (i >= 0 || j >= 0) {
        // Get the digits to subtract shorthand for 0 if we are out of digits
        int num1 = (i >= 0) ? digits_[i] : 0;
        int num2 = (j >= 0) ? other.digits_[j] : 0;

        int diff = num1 - num2 - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        result.digits_.insert(result.digits_.begin(), diff);

        // Update the index
        if (i >= 0) i--;
        if (j >= 0) j--;
    }

    // Check if negative number
    if (borrow) {
        std::cout << "Error: Negative number not allowed." << std::endl;
    }

    // Remove leading zeros
    while (!result.digits_.empty() && result.digits_.front() == 0) {
        result.digits_.erase(result.digits_.begin());
    }

    return result;
}

SuperInt SuperInt::operator*(const SuperInt& other)
{
    SuperInt result;

    // Vector for product
    std::vector<int> product(digits_.size() + other.digits_.size(), 0);

    // Multiply right to left and add to the product
    for (int i = digits_.size() - 1; i >= 0; i--) {
        
        int carry = 0;
        
        for (int j = other.digits_.size() - 1; j >= 0; j--) {
            
            int temp = (digits_[i] * other.digits_[j]) + carry + product[i + j + 1];
            product[i + j + 1] = temp % 10;
            carry = temp / 10;
        }
        product[i] += carry;
    }

    // Copy  product to result, remove leading zeros
    result.digits_.assign(product.begin(), product.end());
    while (!result.digits_.empty() && result.digits_.front() == 0) {
        result.digits_.erase(result.digits_.begin());
    }

    return result;
}

SuperInt SuperInt::operator*(const int& other)
{
    // Create a result object to store the product
    SuperInt result;

    if (other < 0) {
        std::cout << "Error: Negative number not allowed." << std::endl;
        return result;
    }

    int carry = 0;
    for (int i = digits_.size() - 1; i >= 0 || carry; i--) {
        if (i >= 0) {
            int temp = digits_[i] * other + carry;
            result.digits_.insert(result.digits_.begin(), temp % 10);
            carry = temp / 10;
        } else {
            result.digits_.insert(result.digits_.begin(), carry % 10);
            carry /= 10;
        }
    }

    return result;
}

SuperInt SuperInt::operator/(const SuperInt& other)
{
    SuperInt result;

    // Check for divide by zero
    if (other.digits_.empty()) {
        std::cout << "Error: Divide by zero." << std::endl;
        return result;
    }

    // Check for divide by one
    if (other.digits_.size() == 1 && other.digits_[0] == 1) {
        return *this;
    }

    // First check if the sizes are the same, if they are then multiply other by steps until it is larger or equal to
    // this then the step count is the quotient.
    // Multiply step count by other then subtract this by the product to calculate the remainder.
    
    
    // If one is larger than the other then we need to do long division
    // We will shift the divisor to the left until it is the same size as the dividend
    // Then we will do the traditional long division algorithm from before to find the quotient
    // REPEAT, for the number of shifts + 1 tracking the quotients, all of them put together will be the result,
    // the last one will be the remainder
}

SuperInt SuperInt::operator^(const SuperInt& other)
{
    // X^42 = X^32 * X^8 * X^2
    // So start with 1 and multiply by X until we get to 42

    // Do a while loop while(exp != 0) and check if exp is odd (if (exp & 1)) then multiply result by power
    // Then multiply power by itself and divide exp by 2 (exp >>= 1)
}

SuperInt SuperInt::operator%(const SuperInt& other)
{
    
    // Things like a^b % c
    // Something interesting though (a + b) % c = (a % c + b % c) % c
}

SuperInt& SuperInt::operator=(const SuperInt& other)
{
// Check for self assignment
    if (this == &other) {
        return *this;
    }

    // Copy the digits
    digits_ = other.digits_;

    return *this;
}

void SuperInt::operator=(const std::string& other)
{
    for (const char digit_char : other) {
        if (isdigit(digit_char)) {
            digits_.push_back(digit_char - '0');
        }
        else
        {
            std::cout << "Error: Invalid character in number." << std::endl;
        }
    }
}

SuperInt SuperInt::factorial(int n)
{
    if (n < 0) {
        std::cout << "Error: Negative number not allowed." << std::endl;
        return SuperInt();
    }

    SuperInt result("1");

    for (int i = 2; i <= n; i++) {
        result = result * i; 
    }

    return result;
}

int SuperInt::compare(const SuperInt& other) const
{
    // Compare the number of digits for a quick comparison
    if (digits_.size() < other.digits_.size()) {
        return -1; // This is smaller
    }
    if (digits_.size() > other.digits_.size()) {
        return 1; // This is smaller
    }

    // compare digit by digit
    for (size_t i = 0; i < digits_.size(); i++) {
        if (digits_[i] < other.digits_[i]) {
            return -1; // This is smaller
        } else if (digits_[i] > other.digits_[i]) {
            return 1; // This is larger
        }
    }

    // Then its equal
    return 0;
}

int SuperInt::get_int() const
{
    if (digits_.empty()) {
        return 0; 
    }

    int result = 0;
    int multiplier = 1;

    // Convert
    for (int i = digits_.size() - 1; i >= 0; i--) {
        // Check for overflow
        if (result > std::numeric_limits<int>::max() - digits_[i] / multiplier) {
            return 0;
        }

        result += digits_[i] * multiplier;
        multiplier *= 10;
    }

    return result;
}
