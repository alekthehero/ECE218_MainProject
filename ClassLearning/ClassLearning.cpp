#include <iostream>
#include <ostream>
#include "LinkedListClass/Item.h"
#include "LinkedListClass/LinkedList.h"

struct item;

int main(int argc, char* argv[])
{
    
#pragma region LinkedList_Insert
    
    LinkedList<item*> linked_list;
    
    item * item1 = new item("Apple", "123456789", 1);
    item * item2 = new item("Orange", "987654321", 2);
    item * item3 = new item("Banana", "123456789", 3);
    item * item4 = new item("Pear", "987654321", 4);
    item * item5 = new item("Grape", "123456789", 6);
    item * item6 = new item("Peach", "987654321", 7);

    item * itemToInsert = new item("Apple", "123456789", 5);
    
    linked_list.add(item1);
    linked_list.add(item2);
    linked_list.add(item3);
    linked_list.add(item4);
    linked_list.add(item5);
    linked_list.add(item6);

    //Sort  based on price
    link<item> * prev = nullptr;
    link<item>* ptr = linked_list.head();
    while (ptr->next != nullptr & ptr->data->price < itemToInsert->price)
    {
        prev = ptr;
        ptr = ptr->next;
    }
    
    
#pragma endregion


    
    
    return 0;
}

