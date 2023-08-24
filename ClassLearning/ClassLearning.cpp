#include <iostream>
#include <ostream>

#include "ArrayClass/array.h"

int main(int argc, char* argv[])
{
    array A(20);
    for (int i=0; i<20; i++)
    {
        A.set(i, i*i);
    }

    int sum = 0;
    for (int i = 0; i < 20; ++i)
    {
        sum += A.get(i);
    }
    
    std::cout << "sum = " << sum << std::endl;
    std::cout << "A.get_size() = " << A.get_size() << std::endl;
    return 0;
}

