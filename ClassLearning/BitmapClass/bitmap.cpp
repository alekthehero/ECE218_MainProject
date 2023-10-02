#include "bitmap.h"
#include <iostream>
#include <new>

bitmap::~bitmap()
{
    delete[] this->data;
}

bitmap::bitmap()
{
    this->num_bits = 64;
    try
    {
        this->data = new int64[1];
    }
    catch (std::bad_alloc &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << "Could not allocate memory for bitmap." << std::endl;
        exit(1);
    }
}

bitmap::bitmap(const int num_bits)
{
    this->num_bits = num_bits;
    try
    {
        this->data = new int64[num_bits / 64 + 1];
    }
    catch (std::bad_alloc &e)
    {
        std::cout << "Error: " << e.what() << std::endl;
        std::cout << "Could not allocate memory for bitmap." << std::endl;
        exit(1);
    }
}

int bitmap::get(const int index) const
{
    int entry = index/bits_per_int64;
    int bit_pos = index % bits_per_int64;
    if (data[entry]&(1<<bit_pos) != 0)
    {
        return 1;
    }
    return 0;
}

void bitmap::set(const int index, const int value)
{
    int entry = index/bits_per_int64;
    int bit_pos = index % bits_per_int64;
    int mask = 1<<bit_pos;
    if (value == 0)
    {
        data[entry] &= ~mask;
    }
    else
    {
        data[entry] |= mask;
    }
}


