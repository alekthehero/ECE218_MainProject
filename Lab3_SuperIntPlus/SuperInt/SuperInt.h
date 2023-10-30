#pragma once
#include <string>
#include <vector>

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
    SuperInt operator^(const SuperInt& other);
    SuperInt operator%(const SuperInt& other);
    SuperInt& operator=(const SuperInt& other);
    void operator=(const std::string& other);
    SuperInt factorial(int n);
    bool operator<(const SuperInt& other) const;
    bool operator>(const SuperInt& other) const;


    int get_int() const;

protected:
    std::vector<int> digits_;
    bool is_negative_;
};
