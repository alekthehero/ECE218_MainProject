#pragma once

class array
{
public:
    
    array(int size);
    ~array();

    int get(int index) const;
    void set(int index, int value);

    int get_size() const { return size_; }
    
protected:
    
    int size_;
    int* data_;
};
