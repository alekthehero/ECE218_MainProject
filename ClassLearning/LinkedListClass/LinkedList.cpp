#include "LinkedList.h"

#include <iostream>



template <typename any>
void LinkedList<any>::remove(any data)
{
    
}

template <typename any>
any * LinkedList<any>::find(any* data)
{
    link<any> * tempHead = this->head;
    while (tempHead != nullptr)
    {
        if (tempHead->data == data)
        {
            std::cout << "Found" << std::endl;
            return tempHead;
        }
        tempHead = tempHead->next;
    }
}

template <typename any>
any* LinkedList<any>::get(int index)
{
    link<any> * tempHead = this->head;
    for (int i = 0; i < index; i++)
    {
        if (tempHead == nullptr)
        {
            throw std::exception("Index out of bounds");
        }
        tempHead = tempHead->next;
    }
    return tempHead->data;
}

template <typename any>
void LinkedList<any>::print()
{
    link<any> * tempHead = this->head;
    while (tempHead != nullptr)
    {
        std::cout << tempHead->data << std::endl;
        tempHead = tempHead->next;
    }
}