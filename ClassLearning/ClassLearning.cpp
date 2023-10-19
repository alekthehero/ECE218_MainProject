#include <iostream>
#include <ostream>
#include <vector>
#include <string>

#include "LinkedListClass/Item.h"
#include "LinkedListClass/LinkedList.h"

using namespace std;

struct item;

struct pussycat 
{ string name; 
    string colour; 
    int age; 
    int number_of_legs; };

int main(int argc, char* argv[])
{
    
#pragma region LinkedList_Insert
    
    /*LinkedList<item*> linked_list;
    
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
    }*/
    
    
#pragma endregion

#pragma region InsertionSort_Array

    int arr[] = { 9, 11, 13, 10, 6, 7, 1, 2, 3, 4, 5, 6 };

    // Start with a line between sorted and unsorted sections of the array.
    // the main loop will move the line to the right sort those two positions and there values and move to the next
    // section.
    // When the sorting is occuring it needs to take that item if not in the right place and insert it into the right
    // place, for example when sorting 13 and 10, 10 will have to move after 9 and before 11
    

#pragma endregion

#pragma region 3dArray

    /*int arr3D[3][3][2];

    //fill with count
    int count = 0;
    for (int x = 0; x < 3; x++)
        for (int y = 0; y < 3; y++)
            for (int z = 0; z < 2; z++)
                arr3D[x][y][z] = count++;

    for (int x = 0; x < 3; x++)
        for (int y = 0; y < 3; y++)
            for (int z = 0; z < 2; z++)
                std::cout << arr3D[x][y][z] << std::endl;*/

#pragma endregion

#pragma region BubbleSort_Array
    
    // int a[] = {3 ,4 ,6, 2, 1, 5, 7, 9, 8, 10};
    // int len = 10;
    //
    // for(int i = 0; i < len; i ++)
    // {
    //     for (int y = 0; y < len - 1; y ++)
    //     {
    //         if(a[y] > a[y + 1])
    //         {
    //             const int temp = a[y + 1];
    //             a[y + 1] = a[y];
    //             a[y] = temp;
    //         }
    //     }
    // }
    //
    //
    // for (int i : a)
    // {
    //     std::cout << i << std::endl;
    // }

#pragma endregion
    
    return 0;
}

