#include "SuperInt.h"
#include <iostream>
#include <ostream>
#include <limits>


SuperInt::SuperInt()
{
    digits_ = std::vector<int>();
    is_negative_ = false;
}

SuperInt::SuperInt(const SuperInt& other)
{
    digits_ = other.digits_;
    is_negative_ = other.is_negative_;
}

SuperInt::SuperInt(const std::string& str, const bool neg = false)
{
    is_negative_ = neg;
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

void SuperInt::print(std::ostream& out) const
{
    if (this->is_negative_)
        out << "-";
    for (const int digit : digits_) {
        out << std::to_string(digit) << std::endl;
    }
}

std::ostream& SuperInt::operator<<(std::ostream& out) const
{
    if (this->is_negative_)
        out << "-";
    for (const int digit : digits_) {
        out << std::to_string(digit);
    }
    return out;
}

void SuperInt::printf(std::ostream& out) const
{
    size_t char_count = 0;

    if (this->is_negative_)
        out << "-";

    for (const int digit : digits_) {
        out << std::to_string(digit);
        char_count++;

        // new line every 50
        if (char_count % 50 == 0 && char_count < digits_.size()) {
            out << "\n";
        }
    }
}

SuperInt SuperInt::operator+(const SuperInt& other) {
    SuperInt result;
    
    if (this->is_negative_ == other.is_negative_) {
        // Both operands have the same sign, perform addition keep sign
        int carry = 0;
        int i = digits_.size() - 1;
        int j = other.digits_.size() - 1;

        while (i >= 0 || j >= 0 || carry) {
            int sum = carry;
            if (i >= 0) {
                sum += digits_[i];
                i--;
            }
            if (j >= 0) {
                sum += other.digits_[j];
                j--;
            }

            carry = sum / 10;
            sum %= 10;
            result.digits_.insert(result.digits_.begin(), sum);
        }

        result.is_negative_ = this->is_negative_;
    } else {
        result = *this - other;
    }

    return result;
}

SuperInt SuperInt::operator-(const SuperInt& other) const {
    // This is front
    // Other is second
    
    SuperInt result;
    
    SuperInt temp_this = *this;
    SuperInt temp_other = other;

    // Check if other is negative and this is positive, then just add
    if (temp_other.is_negative_ && !temp_this.is_negative_) {
        temp_other.is_negative_ = false;
        return temp_this + temp_other;
    }

    // Check if this is negative and other is positive, then just add and make result negative
    if (!temp_other.is_negative_ && temp_this.is_negative_) {
        temp_this.is_negative_ = false;
        result = temp_this + temp_other;
        result.is_negative_ = true;
        return result;
    }

    // If all three are negative then just add but check if other is larger or smaller to determine sign
    // Other is larger then result is negative, other is smaller then result is positive
    if (temp_other.is_negative_ && temp_this.is_negative_) {
        
        if (temp_this < temp_other) {
            result.is_negative_ = true;
            std::swap(temp_this, temp_other);
        }
        else
        {
            result.is_negative_ = false;
        }

        temp_other.is_negative_ = false;
        temp_this.is_negative_ = false;
        
        result = temp_this - temp_other;
        return result;
    }

    // Check sizes, if other is larger then swap and make result negative, If this is larger then keep result positive
    if (temp_this < temp_other) {
        result.is_negative_ = true;
        std::swap(temp_this, temp_other);
    }
    else
    {
        result.is_negative_ = false;
    }
    
    // Borrow and index
    int borrow = 0;
    int i = temp_this.digits_.size() - 1;
    int j = temp_other.digits_.size() - 1;

    // Subtract right to left
    while (i >= 0 || j >= 0) {
        // Get the digits to subtract shorthand for 0 if we are out of digits
        int num1 = (i >= 0) ? temp_this.digits_[i] : 0;
        int num2 = (j >= 0) ? temp_other.digits_[j] : 0;

        int diff = num1 - num2 - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        
        result.digits_.insert(result.digits_.begin(), diff);
        
        if (i >= 0) i--;
        if (j >= 0) j--;
    }

    // Check if negative number
    if (borrow) {
        std::cout << "Error: Swap didnt work." << "\n" << borrow << std::endl;
    }

    // Remove leading zeros
    while (!result.digits_.empty() && result.digits_.front() == 0) {
        if (result.digits_.size() == 1 && result.digits_[0] == 0) {
            result.is_negative_ = false;
            break;
        }
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

    // Check if negative number
    if (is_negative_ != other.is_negative_) {
        result.is_negative_ = true;
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
    
    if (is_negative_ && other > 0 || !is_negative_ && other < 0) {
        result.is_negative_ = true;
    }

    return result;
}

SuperInt SuperInt::operator/(const SuperInt& other)
{
    SuperInt quotient;
    SuperInt remainder;
    divmod_helper(other, quotient, remainder);
    return quotient;
}

SuperInt SuperInt::operator/(const int& other)
{
    SuperInt intAsSuperInt(std::to_string(other)); 
    return (*this / intAsSuperInt);
}

SuperInt SuperInt::operator^(const SuperInt& other)
{
    SuperInt result = SuperInt("1");
    SuperInt base = *this;
    SuperInt exponent = other;

    // Handle special cases
    if (exponent.digits_.empty()) {
        return SuperInt("1");
    } else if (exponent.digits_.size() == 1 && exponent.digits_[0] == 1) {
        return base;
    } else if (exponent.is_negative_ == true) {
        throw std::invalid_argument("Negative exponents are not supported.");
    }

    while (!exponent.is_zero()) {
        if (exponent % 2 == 1) {
            result = result * base;
        }
        base = base * base;
        exponent = exponent / 2;
    }

    return result;
}

SuperInt SuperInt::operator%(const SuperInt& other)
{
    SuperInt quotient;
    SuperInt remainder;
    divmod_helper(other, quotient, remainder);
    return remainder;
}

SuperInt SuperInt::operator%(const int& other)
{
    SuperInt intAsSuperInt(std::to_string(other));
    return (*this % intAsSuperInt);
}

SuperInt& SuperInt::operator=(const SuperInt& other)
{
    if (this == &other) {
        return *this;
    }
    
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

SuperInt SuperInt::powmod(SuperInt& pow, SuperInt& mod)
{
    SuperInt result("1");
    SuperInt base(*this);

    while (!pow.is_zero()) {
        if (pow % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        pow = pow / 2;
    }

    return result;
}

SuperInt SuperInt::random(int lower, int upper)
{
    if (lower > upper) {
        throw std::invalid_argument("Lower bound should be less than or equal to the upper bound.");
    }

    SuperInt result;
    
    int numDigits = rand() % (upper - lower + 1) + lower;
    
    if (numDigits % 2 == 1)
    {
        result.is_negative_ = true;
    }
    
    for (int i = 0; i < numDigits; ++i) {
        int digit = (i == 0) ? rand() % 9 + 1 : rand() % 10;
        result.digits_.push_back(digit);
    }

    return result;
}

SuperInt SuperInt::gcd(SuperInt first, SuperInt second)
{
    SuperInt x, t;
    
    first.is_negative_ = false;
    second.is_negative_ = false;

    while (!second.is_zero()) {
        t = first;
        first = second;
        SuperInt qoutient = SuperInt();
        t.divmod_helper(second, qoutient, x);
        second = x;
    }

    first.is_negative_ = false;

    return first;
}

bool SuperInt::operator<(const SuperInt& other) const {
    
    if (is_negative_ && !other.is_negative_) {
       
        return true;
    } else if (!is_negative_ && other.is_negative_) {
    
        return false;
    } else if (is_negative_ && other.is_negative_) {
       
        if (digits_.size() > other.digits_.size()) {
            return false;
        } else if (digits_.size() < other.digits_.size()) {
            return true;
        } else {
            for (size_t i = 0; i < digits_.size(); ++i) {
                if (digits_[i] < other.digits_[i]) {
                    return false;
                } else if (digits_[i] > other.digits_[i]) {
                    return true;
                }
            }
            return false; 
        }
    } else {
       
        if (digits_.size() < other.digits_.size()) {
            return true;
        } else if (digits_.size() > other.digits_.size()) {
            return false;
        } else {
            for (size_t i = 0; i < digits_.size(); ++i) {
                if (digits_[i] < other.digits_[i]) {
                    return true;
                } else if (digits_[i] > other.digits_[i]) {
                    return false;
                }
            }
            return false;
        }
    }
}

bool SuperInt::operator>(const SuperInt& other) const {
  
    if (is_negative_ && !other.is_negative_) {
        return false;
    } else if (!is_negative_ && other.is_negative_) {
        return true;
    } else if (is_negative_ && other.is_negative_) {
        if (digits_.size() > other.digits_.size()) {
            return true;
        } else if (digits_.size() < other.digits_.size()) {
            return false;
        } else {
            for (size_t i = 0; i < digits_.size(); ++i) {
                if (digits_[i] > other.digits_[i]) {
                    return true;
                } else if (digits_[i] < other.digits_[i]) {
                    return false;
                }
            }
            return false; 
        }
    } else {
        if (digits_.size() < other.digits_.size()) {
            return false;
        } else if (digits_.size() > other.digits_.size()) {
            return true;
        } else {
            for (size_t i = 0; i < digits_.size(); ++i) {
                if (digits_[i] > other.digits_[i]) {
                    return true;
                } else if (digits_[i] < other.digits_[i]) {
                    return false;
                }
            }
            return false; 
        }
    }
}

bool SuperInt::operator==(const SuperInt& other) const
{
    
    if (is_negative_ != other.is_negative_) {
        return false;
    }
    
    if (digits_.size() != other.digits_.size()) {
        return false;
    }
    
    for (size_t i = 0; i < digits_.size(); ++i) {
        if (digits_[i] != other.digits_[i]) {
            return false;
        }
    }
    
    return true;
}

bool SuperInt::operator==(int i) const
{
    SuperInt compare = SuperInt(std::to_string(i));
    return *this == compare;
}

bool SuperInt::operator>=(const SuperInt& other) const
{
    return (*this > other) || (*this == other);
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

bool SuperInt::is_zero() const
{
    for (const int digit : digits_)
    {
        if (digit != 0) {
            return false;
        }
    }
    return true;
}

void SuperInt::divmod_helper(const SuperInt& other, SuperInt& quotient, SuperInt& remainder)
{
    if (other.digits_.size() == 1 && other.digits_[0] == 0) {
        throw std::invalid_argument("Division by zero is not allowed.");
    }

    SuperInt dividend = *this;  
    SuperInt divisor = other;
    quotient = SuperInt();  
    remainder = SuperInt();

    // Get result sign
    bool isNegative = (dividend.is_negative_ != divisor.is_negative_);

    // Make both dividend and divisor positive for simplicity
    dividend.is_negative_ = false;
    divisor.is_negative_ = false;

    while (dividend >= divisor) {
        SuperInt temp_divisor = divisor;
        SuperInt temp_quotient = SuperInt("1");

        while (dividend >= temp_divisor) {
            dividend = dividend - temp_divisor;
            quotient = quotient + temp_quotient;
            temp_divisor * 2; 
            temp_quotient * 2; 
        }
    }

    // Set the sign of the result
    if (isNegative) {
        quotient.is_negative_ = true;
    }

    // Set the sign of the remainder to match the dividend
    if (this->is_negative_) {
        remainder = dividend;
        remainder.is_negative_ = true;
    } else {
        remainder = dividend;
    }
}
