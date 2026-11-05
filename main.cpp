/*
=====================================================================

                  GDSL - DEMONSTRATION PROGRAM

=====================================================================

Author       : Sarthak Salunke
Date         : 4/7/2024

Description  :

This file demonstrates the usage of the classes and functions
provided by the GDSL library.

=====================================================================
*/

#include <iostream>
#include <vector>
#include "GDSL.h"

using namespace std;

//=====================================================================
//
//                  SECTION 1 : SINGLY LINEAR LINKED LIST
//
//=====================================================================

void SinglyLinkedListDemo()
{
    cout << "\n--- Singly Linear Linked List ---\n";

    GDSL::SinglyLL<int> list;
    list.InsertFirst(10);
    list.InsertLast(20);
    list.InsertLast(30);
    list.InsertAtPos(15, 2);

    list.Display();
    cout << "Count: " << list.Count() << '\n';
    cout << "First occurrence of 20: " << list.SearchFirstOccurrence(20) << '\n';
    cout << "Last occurrence of 20: " << list.SearchLastOccurrence(20) << '\n';

    int middle = 0;
    if (list.MiddleElement(middle)) cout << "Middle element: " << middle << '\n';
    cout << "Contains a loop: " << boolalpha << list.CheckLoop() << '\n';

    list.Reverse();
    cout << "After reverse: ";
    list.Display();
}

//=====================================================================
//
//                  SECTION 2 : DOUBLY LINEAR LINKED LIST
//
//=====================================================================

void DoublyLinkedListDemo()
{
    cout << "\n--- Doubly Linear Linked List ---\n";
    GDSL::DoublyLL<int> list;
    list.InsertFirst(100);
    list.InsertLast(200);
    list.InsertLast(300);
    list.Display();
    cout << "Count: " << list.Count() << '\n';
}

//=====================================================================
//
//                  SECTION 3 : SINGLY CIRCULAR LINKED LIST
//
//=====================================================================

void SinglyCircularListDemo()
{
    cout << "\n--- Singly Circular Linked List ---\n";
    GDSL::SinglyCL<int> list;
    list.InsertFirst(1);
    list.InsertLast(2);
    list.InsertLast(3);
    list.Display();
    cout << "Count: " << list.Count() << '\n';
}

//=====================================================================
//
//                  SECTION 4 : DOUBLY CIRCULAR LINKED LIST
//
//=====================================================================

void DoublyCircularListDemo()
{
    cout << "\n--- Doubly Circular Linked List ---\n";
    GDSL::DoublyCL<int> list;
    list.InsertFirst(11);
    list.InsertLast(22);
    list.InsertLast(33);
    list.Display();
    cout << "Count: " << list.Count() << '\n';
}

//=====================================================================
//
//                  SECTION 5 : STACK
//
//=====================================================================

void StackDemo()
{
    cout << "\n--- Stack ---\n";
    GDSL::Stack<int> stack;
    stack.Push(10);
    stack.Push(20);
    stack.Push(30);
    stack.Display();
    cout << "Count: " << stack.Count() << '\n';
    cout << "Is empty: " << boolalpha << stack.IsEmpty() << '\n';
    stack.Pop();
    stack.Display();
}

//=====================================================================
//
//                  SECTION 6 : QUEUE
//
//=====================================================================

void QueueDemo()
{
    cout << "\n--- Queue ---\n";
    GDSL::Queue<int> queue;
    queue.Enqueue(10);
    queue.Enqueue(20);
    queue.Enqueue(30);
    queue.Display();
    cout << "Count: " << queue.Count() << '\n';
    queue.Dequeue();
    queue.Display();
}

//=====================================================================
//
//                  SECTION 7 : DYNAMIC ARRAY
//
//=====================================================================

void DynamicArrayDemo()
{
    cout << "\n--- Dynamic Array ---\n";
    GDSL::Array<int> values;
    values.PushBack(40);
    values.PushBack(10);
    values.PushBack(30);
    values.PushBack(20);
    values.Display();
    cout << "Size: " << values.Size() << '\n';
}

//=====================================================================
//
//                  SECTION 8 : SEARCHING ALGORITHMS
//
//=====================================================================

void SearchingDemo()
{
    cout << "\n--- Searching Algorithms ---\n";
    vector<int> values = {10, 20, 30, 40, 50};

    cout << "Linear search (30): "
         << GDSL::LinearSearch(values, 30) << '\n';
    cout << "Bidirectional search (50): "
         << GDSL::BiDirectionalSearch(values, 50) << '\n';
    cout << "Binary search (40): "
         << GDSL::BinarySearch(values, 40) << '\n';
    cout << "Search results are zero-based indexes; -1 means not found.\n";
}

//=====================================================================
//
//                  SECTION 9 : SORTING ALGORITHMS
//
//=====================================================================

void SortingDemo()
{
    cout << "\n--- Sorting Algorithms ---\n";
    vector<int> values = {50, 20, 40, 10, 30};

    cout << "Original: ";
    GDSL::Display(values);

    vector<int> bubble = values;
    GDSL::BubbleSort(bubble);
    cout << "Bubble sort: ";
    GDSL::Display(bubble);

    vector<int> efficient = values;
    GDSL::BubbleSortEfficient(efficient);
    cout << "Efficient bubble sort: ";
    GDSL::Display(efficient);

    vector<int> selection = values;
    GDSL::SelectionSort(selection);
    cout << "Selection sort: ";
    GDSL::Display(selection);

    vector<int> insertion = values;
    GDSL::InsertionSort(insertion);
    cout << "Insertion sort: ";
    GDSL::Display(insertion);
}

//=====================================================================
//
//                  SECTION 10 : BINARY SEARCH TREE
//
//=====================================================================

void BinarySearchTreeDemo()
{
    cout << "\n--- Binary Search Tree ---\n";
    GDSL::BinarySearchTree<int> tree;

    tree.Insert(50);
    tree.Insert(30);
    tree.Insert(70);
    tree.Insert(20);
    tree.Insert(40);
    tree.Insert(60);
    tree.Insert(80);
    tree.Insert(30); // Duplicate: ignored.

    cout << "Inorder: ";
    tree.Inorder();
    cout << "Preorder: ";
    tree.Preorder();
    cout << "Postorder: ";
    tree.Postorder();

    cout << "Search 60: " << boolalpha << tree.Search(60) << '\n';
    cout << "Leaf nodes: " << tree.CountLeaf() << '\n';
    cout << "Parent nodes: " << tree.CountParent() << '\n';
    cout << "Total nodes: " << tree.CountAll() << '\n';
}

//=====================================================================
//
//                  MAIN FUNCTION
//
//=====================================================================

int main()
{
    SinglyLinkedListDemo();
    DoublyLinkedListDemo();
    SinglyCircularListDemo();
    DoublyCircularListDemo();
    StackDemo();
    QueueDemo();
    DynamicArrayDemo();
    SearchingDemo();
    SortingDemo();
    BinarySearchTreeDemo();

    return 0;
}
