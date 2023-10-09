#pragma once

#include "Link.h"

template <typename any>
class LinkedList
{
public:
    LinkedList(): head(nullptr) {};

    void add(any data)
    {
        head = new link<any>(data, head);
    }
    void remove(any data);
    any * find(any * data);
    any * get(int index);
    void print();
    
    link<any> * head;
    
};
