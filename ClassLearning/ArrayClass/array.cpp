#include "array.h"
#include <cassert>


array::array(const int size)
{
    this->size_ = size;
    data_ = new int[size];
}

array::~array()
{
    delete[] data_;
}

int array::get(const int index) const
{
    assert(index >= 0 && index < size_);
    return data_[index];
}

// ReSharper disable once CppMemberFunctionMayBeConst
void array::set(const int index, const int value)
{
    assert(index >= 0 && index < size_);
    data_[index] = value;
}

