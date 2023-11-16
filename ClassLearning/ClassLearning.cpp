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

void merge(int a[], int l, int mid, int r);
void mergeSort(int a[], int l, int r);

int main(int argc, char* argv[])
{
    int arr[] = { 9, 11, 13, 10, 6, 7, 1, 2, 3, 4, 5, 17};
    
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

    // int arr[] = { 9, 11, 13, 10, 6, 7, 1, 2, 3, 4, 5, 6 };
    // int length = 12;
    //
    // // Start with a line between sorted and unsorted sections of the array.
    // // the main loop will move the line to the right sort those two positions and there values and move to the next
    // // section.
    // // When the sorting is occuring it needs to take that item if not in the right place and insert it into the right
    // // place, for example when sorting 13 and 10, 10 will have to move after 9 and before 11
    //
    // for(int i = 1; i < length; i++)
    // {
    //     int key = arr[i];
    //     int j = i - 1;
    //     while(j >= 0 && arr[j] > key)
    //     {
    //         arr[j + 1] = arr[j];
    //         j = j - 1;
    //     }
    //     arr[j + 1] = key;
    // }
    //
    // for(int i : arr)
    // {
    //     cout << i << endl;
    // }

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

#pragma region SelectionSort
    
    /*int arr[] = { 9, 11, 13, 10, 6, 7, 1, 2, 3, 4, 5, 6 };
    int length = 12;

    for (int i = 0; i < length - 1; i ++)
    {
        int minPos = i;
        for(int j = i + 1; j < length; j++)
        {
            if (arr[minPos] < arr[j])
            {
                minPos = j;
            }
        }
        if(minPos != i)
        {
            int temp = arr[i];
            arr[i] = arr[minPos];
            arr[minPos] = temp;
        }
    }

    for (int i: arr)
    {
        cout << i << endl;
    }*/

#pragma endregion

#pragma region Merge Sort Array

    /*
    mergeSort(arr, 0, 12-1);

    for(int i = 0; i < 12; i ++)
    {
        cout<< arr[i] << " ";
    }
    */

    

#pragma endregion

#pragma region Merge Sort Linked List

    
    
    
#pragma endregion
    return 0;
}

void merge(int a[], int l, int mid, int r)
{
    int LeftSub = l;
    int RightSub = mid+1;
    int TempSub = l;

    int temp[12];

    // Ensureing the sub arrays dont go out of bounds
    while(LeftSub <= mid && RightSub <= r)
    {
        // Do comparisons
        
        if(a[LeftSub] <= a[RightSub])
        {
            // If the current index in left sub is less then right sub then put left in temp sub
            temp[TempSub] = a[LeftSub];
            // Move indexes up
            LeftSub++;
            TempSub++;
        }
        else
        {
            temp[TempSub] = a[RightSub];
            // Move indexes up
            RightSub++;
            TempSub++;
        }
    }

    //In case the sub arrays are not even length
    while (LeftSub <= mid)
    {
        temp[TempSub] = a[LeftSub];
        LeftSub++;
        TempSub++;
    }
    while (RightSub <= r)
    {
        temp[TempSub] = a[RightSub];
        RightSub++;
        TempSub++;
    }

    // Put into original array
    for(int s = l; s < r; s++)
    {
        a[s] = temp[s];
    }
}

void mergeSort(int a[], int l, int r)
{
    if (l < r)
    {
        int mid = (l+r)/2;
        mergeSort(a, l, mid);
        mergeSort(a, mid+1, r);
        merge(a, l, mid, r);
    }
}



