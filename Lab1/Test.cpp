#include "Headers/Test.h"

#include <iostream>
#include <ostream>


Test::Test(int num)
{
    data = num;
}

void Test::print()
{
    std::cout << data << std::endl;
}

