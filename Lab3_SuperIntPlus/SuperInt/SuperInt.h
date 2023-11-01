#pragma once
#include <string>
#include <vector>
#include <random>

class SuperInt
{
public:
    SuperInt();
    SuperInt(const SuperInt& other);
    SuperInt(const std::string& str, const bool neg);

    void print(std::ostream& out) const;
    std::ostream& operator<<(std::ostream& out) const;
    
    void printf(std::ostream& out) const;
    
    SuperInt operator+(const SuperInt& other);
    SuperInt operator-(const SuperInt& other) const;
    SuperInt operator*(const SuperInt& other);
    SuperInt operator*(const int& other);
    SuperInt operator/(const SuperInt& other);
    SuperInt operator/(const int& other);
    SuperInt operator%(const SuperInt& other);
    SuperInt operator%(const int& other);
    SuperInt operator^(const SuperInt& other);
    SuperInt operator^(const int& other);
    SuperInt& operator=(const SuperInt& other);
    void operator=(const std::string& other);
    bool operator<(const SuperInt& other) const;
    bool operator>(const SuperInt& other) const;
    bool operator==(const SuperInt& other) const;
    bool operator==(int i) const;
    bool operator>=(const SuperInt& divisor) const;

    SuperInt factorial(int n);
    SuperInt powmod(SuperInt &pow, SuperInt &mod);
    SuperInt random(int lower, int upper);
    static SuperInt gcd (SuperInt a, SuperInt b);
    
    int get_int() const;

private:

    bool is_zero() const;
    void divmod_helper(const SuperInt& other, SuperInt& quotient, SuperInt& remainder);
    
protected:
    std::vector<int> digits_;
    bool is_negative_;
};
