#include "Item.h"

#include <iostream>
#include <ostream>

//constructor
item::item(const std::string& name, const std::string& upc, const int price)
{
    this->name = name;
    this->upc = upc;
    this->price = price;
}

//print the item
void item::print()
{
    std::cout << "Name: " << name << std::endl;
    std::cout << "UPC: " << upc << std::endl;
    std::cout << "Price: " << price << std::endl;
}