#include <iostream>
#include <ostream>

#include "LinkedListClass/Item.h"
#include "LinkedListClass/LinkedList.h"

struct item;

int main(int argc, char* argv[])
{
    LinkedList<item*> list;

    item * item1 = new item("Apple", "123456789", 1);
    item * item2 = new item("Orange", "987654321", 2);
    item * shop[100];

    list.add(item1);
    list.add(shop[2]);
    
    
    //std::cout << list.get(0) << std::endl;
    
}

