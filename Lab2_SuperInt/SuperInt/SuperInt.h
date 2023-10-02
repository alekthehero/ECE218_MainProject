#pragma once
#include <string>
#include <vector>
typedef unsigned char digit;

class SuperInt
{
public:
    SuperInt();
    SuperInt(const SuperInt& other);
    SuperInt(const std::string& str);
    ~SuperInt();

    void print(std::ostream& out) const;
    std::ostream& operator<<(std::ostream& out) const;
    
    void printf(std::ostream& out) const;

    SuperInt operator+(const SuperInt& other);
    SuperInt operator-(const SuperInt& other);
    SuperInt operator*(const SuperInt& other);
    SuperInt operator*(const int& other);
    SuperInt& operator=(const SuperInt& other);
    void operator=(const std::string& other);
    SuperInt factorial(int n);
    int compare(const SuperInt& other) const;
    
    int get_int() const;

protected:
    std::vector<int> digits_;
};
