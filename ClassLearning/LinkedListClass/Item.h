#pragma once
#include <string>

struct item
{
protected:
    std::string name;
    std::string upc;
    int price;

public:
    item() = default;
    item(const std::string& name, const std::string& upc, const int price);

    void print();
    
};
