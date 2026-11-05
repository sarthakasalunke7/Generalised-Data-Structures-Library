/*
=====================================================================

              GDSL - GENERALISED DATA STRUCTURES LIBRARY

=====================================================================

Author       : Sarthak Salunke
Date         : 4/7/2024

Description  :

This file contains the complete implementation of the
Generalised Data Structures Library (GDSL).

The library provides reusable implementations of fundamental
data structures and algorithms using C++.

Core Functionalities:

1. Singly Linear Linked List
2. Singly Circular Linked List
3. Doubly Linear Linked List
4. Doubly Circular Linked List
5. Stack
6. Queue
7. Dynamic Array
8. Searching Algorithms
9. Sorting Algorithms
10. Binary Search Tree

=====================================================================
*/

#ifndef GDSL_H
#define GDSL_H

#include <iostream>
#include <vector>
#include <utility>
#include <cstddef>
#include <stdexcept>

namespace GDSL
{

// ============================================================
// 1. SINGLY LINEAR LINKED LIST
// ============================================================

template <class T>
struct nodeSL
{
    T data;
    nodeSL<T>* next;
};

template <class T>
class SinglyLL
{
private:
    nodeSL<T>* First;
    int iCount;

public:
    SinglyLL() : First(nullptr), iCount(0) {}

    ~SinglyLL()
    {
        while (First != nullptr)
        {
            nodeSL<T>* temp = First;
            First = First->next;
            delete temp;
        }
    }

    SinglyLL(const SinglyLL&) = delete;
    SinglyLL& operator=(const SinglyLL&) = delete;

    void Display() const
    {
        nodeSL<T>* temp = First;
        while (temp != nullptr)
        {
            std::cout << "| " << temp->data << " | -> ";
            temp = temp->next;
        }
        std::cout << "NULL\n";
    }

    int Count() const { return iCount; }

    void InsertFirst(T No)
    {
        nodeSL<T>* newn = new nodeSL<T>{No, First};
        First = newn;
        ++iCount;
    }

    void InsertLast(T No)
    {
        nodeSL<T>* newn = new nodeSL<T>{No, nullptr};

        if (First == nullptr)
            First = newn;
        else
        {
            nodeSL<T>* temp = First;
            while (temp->next != nullptr)
                temp = temp->next;
            temp->next = newn;
        }
        ++iCount;
    }

    void InsertAtPos(T No, int iPos)
    {
        if (iPos < 1 || iPos > iCount + 1)
        {
            std::cout << "Invalid position\n";
            return;
        }

        if (iPos == 1) { InsertFirst(No); return; }
        if (iPos == iCount + 1) { InsertLast(No); return; }

        nodeSL<T>* temp = First;
        for (int i = 1; i < iPos - 1; ++i)
            temp = temp->next;

        temp->next = new nodeSL<T>{No, temp->next};
        ++iCount;
    }

    void DeleteFirst()
    {
        if (First == nullptr)
        {
            std::cout << "Linked list is empty\n";
            return;
        }

        nodeSL<T>* temp = First;
        First = First->next;
        delete temp;
        --iCount;
    }

    void DeleteLast()
    {
        if (First == nullptr)
        {
            std::cout << "Linked list is empty\n";
            return;
        }

        if (First->next == nullptr)
        {
            delete First;
            First = nullptr;
        }
        else
        {
            nodeSL<T>* temp = First;
            while (temp->next->next != nullptr)
                temp = temp->next;

            delete temp->next;
            temp->next = nullptr;
        }
        --iCount;
    }

    void DeleteAtPos(int iPos)
    {
        if (iPos < 1 || iPos > iCount)
        {
            std::cout << "Invalid position\n";
            return;
        }

        if (iPos == 1) { DeleteFirst(); return; }
        if (iPos == iCount) { DeleteLast(); return; }

        nodeSL<T>* temp = First;
        for (int i = 1; i < iPos - 1; ++i)
            temp = temp->next;

        nodeSL<T>* target = temp->next;
        temp->next = target->next;
        delete target;
        --iCount;
    }


    bool Search(const T& value) const
    {
        for (nodeSL<T>* temp = First; temp != nullptr; temp = temp->next)
            if (temp->data == value) return true;
        return false;
    }

    // Positions are 1-based. Returns -1 when the value is not found.
    int SearchFirstOccurrence(const T& value) const
    {
        int position = 1;
        for (nodeSL<T>* temp = First; temp != nullptr; temp = temp->next, ++position)
            if (temp->data == value) return position;
        return -1;
    }

    int SearchLastOccurrence(const T& value) const
    {
        int position = 1;
        int result = -1;
        for (nodeSL<T>* temp = First; temp != nullptr; temp = temp->next, ++position)
            if (temp->data == value) result = position;
        return result;
    }

    // Returns false for an empty list; otherwise writes the middle value.
    // For an even number of nodes, this returns the second (upper) middle.
    bool MiddleElement(T& result) const
    {
        if (First == nullptr) return false;

        nodeSL<T>* slow = First;
        nodeSL<T>* fast = First;
        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;
        }
        result = slow->data;
        return true;
    }

    // Floyd's cycle-detection algorithm (tortoise and hare).
    // The normal public operations maintain a linear list, but this method
    // provides a standard linked-list cycle check.
    bool CheckLoop() const
    {
        nodeSL<T>* slow = First;
        nodeSL<T>* fast = First;

        while (fast != nullptr && fast->next != nullptr)
        {
            slow = slow->next;
            fast = fast->next->next;

            if (slow == fast)
                return true;
        }
        return false;
    }

    void Reverse()
    {
        nodeSL<T>* previous = nullptr;
        nodeSL<T>* current = First;

        while (current != nullptr)
        {
            nodeSL<T>* next = current->next;
            current->next = previous;
            previous = current;
            current = next;
        }
        First = previous;
    }
};

// ============================================================
// 2. DOUBLY CIRCULAR LINKED LIST
// ============================================================

template <class T>
struct nodeDC
{
    T data;
    nodeDC<T>* next;
    nodeDC<T>* prev;
};

template <class T>
class DoublyCL
{
private:
    nodeDC<T>* First;
    nodeDC<T>* Last;
    int iCount;

public:
    DoublyCL() : First(nullptr), Last(nullptr), iCount(0) {}

    ~DoublyCL()
    {
        while (iCount > 0)
            DeleteFirst();
    }

    DoublyCL(const DoublyCL&) = delete;
    DoublyCL& operator=(const DoublyCL&) = delete;

    void Display() const
    {
        if (First == nullptr)
        {
            std::cout << "Linked list is empty\n";
            return;
        }

        nodeDC<T>* temp = First;
        std::cout << "<=> ";
        do
        {
            std::cout << "| " << temp->data << " | <=> ";
            temp = temp->next;
        } while (temp != First);
        std::cout << "(back to First)\n";
    }

    int Count() const { return iCount; }

    void InsertFirst(T No)
    {
        nodeDC<T>* newn = new nodeDC<T>{No, nullptr, nullptr};

        if (First == nullptr)
        {
            First = Last = newn;
            newn->next = newn;
            newn->prev = newn;
        }
        else
        {
            newn->next = First;
            newn->prev = Last;
            First->prev = newn;
            Last->next = newn;
            First = newn;
        }
        ++iCount;
    }

    void InsertLast(T No)
    {
        nodeDC<T>* newn = new nodeDC<T>{No, nullptr, nullptr};

        if (First == nullptr)
        {
            First = Last = newn;
            newn->next = newn;
            newn->prev = newn;
        }
        else
        {
            newn->prev = Last;
            newn->next = First;
            Last->next = newn;
            First->prev = newn;
            Last = newn;
        }
        ++iCount;
    }

    void InsertAtPos(T No, int iPos)
    {
        if (iPos < 1 || iPos > iCount + 1)
        {
            std::cout << "Invalid position\n";
            return;
        }
        if (iPos == 1) { InsertFirst(No); return; }
        if (iPos == iCount + 1) { InsertLast(No); return; }

        nodeDC<T>* current = First;
        for (int i = 1; i < iPos; ++i)
            current = current->next;

        nodeDC<T>* newn = new nodeDC<T>{No, current, current->prev};
        current->prev->next = newn;
        current->prev = newn;
        ++iCount;
    }

    void DeleteFirst()
    {
        if (First == nullptr)
        {
            std::cout << "Linked list is empty\n";
            return;
        }

        if (First == Last)
        {
            delete First;
            First = Last = nullptr;
        }
        else
        {
            nodeDC<T>* temp = First;
            First = First->next;
            First->prev = Last;
            Last->next = First;
            delete temp;
        }
        --iCount;
    }

    void DeleteLast()
    {
        if (Last == nullptr)
        {
            std::cout << "Linked list is empty\n";
            return;
        }

        if (First == Last)
        {
            delete Last;
            First = Last = nullptr;
        }
        else
        {
            nodeDC<T>* temp = Last;
            Last = Last->prev;
            Last->next = First;
            First->prev = Last;
            delete temp;
        }
        --iCount;
    }

    void DeleteAtPos(int iPos)
    {
        if (iPos < 1 || iPos > iCount)
        {
            std::cout << "Invalid position\n";
            return;
        }
        if (iPos == 1) { DeleteFirst(); return; }
        if (iPos == iCount) { DeleteLast(); return; }

        nodeDC<T>* target = First;
        for (int i = 1; i < iPos; ++i)
            target = target->next;

        target->prev->next = target->next;
        target->next->prev = target->prev;
        delete target;
        --iCount;
    }
};

// ============================================================
// 3. DOUBLY LINEAR LINKED LIST
// ============================================================

template <class T>
struct nodeDL
{
    T data;
    nodeDL<T>* next;
    nodeDL<T>* prev;
};

template <class T>
class DoublyLL
{
private:
    nodeDL<T>* First;
    nodeDL<T>* Last;
    int iCount;

public:
    DoublyLL() : First(nullptr), Last(nullptr), iCount(0) {}

    ~DoublyLL()
    {
        while (First != nullptr)
        {
            nodeDL<T>* temp = First;
            First = First->next;
            delete temp;
        }
    }

    DoublyLL(const DoublyLL&) = delete;
    DoublyLL& operator=(const DoublyLL&) = delete;

    void Display() const
    {
        nodeDL<T>* temp = First;
        while (temp != nullptr)
        {
            std::cout << "<=> | " << temp->data << " | ";
            temp = temp->next;
        }
        std::cout << "<=> NULL\n";
    }

    int Count() const { return iCount; }

    void InsertFirst(T No)
    {
        nodeDL<T>* newn = new nodeDL<T>{No, First, nullptr};
        if (First == nullptr)
            Last = newn;
        else
            First->prev = newn;
        First = newn;
        ++iCount;
    }

    void InsertLast(T No)
    {
        nodeDL<T>* newn = new nodeDL<T>{No, nullptr, Last};
        if (Last == nullptr)
            First = newn;
        else
            Last->next = newn;
        Last = newn;
        ++iCount;
    }

    void InsertAtPos(T No, int iPos)
    {
        if (iPos < 1 || iPos > iCount + 1)
        {
            std::cout << "Invalid position\n";
            return;
        }
        if (iPos == 1) { InsertFirst(No); return; }
        if (iPos == iCount + 1) { InsertLast(No); return; }

        nodeDL<T>* current = First;
        for (int i = 1; i < iPos; ++i)
            current = current->next;

        nodeDL<T>* newn = new nodeDL<T>{No, current, current->prev};
        current->prev->next = newn;
        current->prev = newn;
        ++iCount;
    }

    void DeleteFirst()
    {
        if (First == nullptr)
        {
            std::cout << "Linked list is empty\n";
            return;
        }

        nodeDL<T>* temp = First;
        First = First->next;
        if (First == nullptr)
            Last = nullptr;
        else
            First->prev = nullptr;
        delete temp;
        --iCount;
    }

    void DeleteLast()
    {
        if (Last == nullptr)
        {
            std::cout << "Linked list is empty\n";
            return;
        }

        nodeDL<T>* temp = Last;
        Last = Last->prev;
        if (Last == nullptr)
            First = nullptr;
        else
            Last->next = nullptr;
        delete temp;
        --iCount;
    }

    void DeleteAtPos(int iPos)
    {
        if (iPos < 1 || iPos > iCount)
        {
            std::cout << "Invalid position\n";
            return;
        }
        if (iPos == 1) { DeleteFirst(); return; }
        if (iPos == iCount) { DeleteLast(); return; }

        nodeDL<T>* target = First;
        for (int i = 1; i < iPos; ++i)
            target = target->next;

        target->prev->next = target->next;
        target->next->prev = target->prev;
        delete target;
        --iCount;
    }
};

// ============================================================
// 4. SINGLY CIRCULAR LINKED LIST
// ============================================================

template <class T>
struct nodeSC
{
    T data;
    nodeSC<T>* next;
};

template <class T>
class SinglyCL
{
private:
    nodeSC<T>* First;
    nodeSC<T>* Last;
    int iCount;

public:
    SinglyCL() : First(nullptr), Last(nullptr), iCount(0) {}

    ~SinglyCL()
    {
        while (iCount > 0)
            DeleteFirst();
    }

    SinglyCL(const SinglyCL&) = delete;
    SinglyCL& operator=(const SinglyCL&) = delete;

    void Display() const
    {
        if (First == nullptr)
        {
            std::cout << "Linked list is empty\n";
            return;
        }

        nodeSC<T>* temp = First;
        do
        {
            std::cout << "| " << temp->data << " | -> ";
            temp = temp->next;
        } while (temp != First);
        std::cout << "(back to First)\n";
    }

    int Count() const { return iCount; }

    void InsertFirst(T No)
    {
        nodeSC<T>* newn = new nodeSC<T>{No, nullptr};

        if (First == nullptr)
        {
            First = Last = newn;
            Last->next = First;
        }
        else
        {
            newn->next = First;
            First = newn;
            Last->next = First;
        }
        ++iCount;
    }

    void InsertLast(T No)
    {
        nodeSC<T>* newn = new nodeSC<T>{No, nullptr};

        if (First == nullptr)
        {
            First = Last = newn;
            Last->next = First;
        }
        else
        {
            Last->next = newn;
            Last = newn;
            Last->next = First;
        }
        ++iCount;
    }

    void InsertAtPos(T No, int iPos)
    {
        if (iPos < 1 || iPos > iCount + 1)
        {
            std::cout << "Invalid position\n";
            return;
        }
        if (iPos == 1) { InsertFirst(No); return; }
        if (iPos == iCount + 1) { InsertLast(No); return; }

        nodeSC<T>* temp = First;
        for (int i = 1; i < iPos - 1; ++i)
            temp = temp->next;

        temp->next = new nodeSC<T>{No, temp->next};
        ++iCount;
    }

    void DeleteFirst()
    {
        if (First == nullptr)
        {
            std::cout << "Linked list is empty\n";
            return;
        }

        if (First == Last)
        {
            delete First;
            First = Last = nullptr;
        }
        else
        {
            nodeSC<T>* temp = First;
            First = First->next;
            Last->next = First;
            delete temp;
        }
        --iCount;
    }

    void DeleteLast()
    {
        if (First == nullptr)
        {
            std::cout << "Linked list is empty\n";
            return;
        }

        if (First == Last)
        {
            delete First;
            First = Last = nullptr;
        }
        else
        {
            nodeSC<T>* temp = First;
            while (temp->next != Last)
                temp = temp->next;

            delete Last;
            Last = temp;
            Last->next = First;
        }
        --iCount;
    }

    void DeleteAtPos(int iPos)
    {
        if (iPos < 1 || iPos > iCount)
        {
            std::cout << "Invalid position\n";
            return;
        }
        if (iPos == 1) { DeleteFirst(); return; }
        if (iPos == iCount) { DeleteLast(); return; }

        nodeSC<T>* temp = First;
        for (int i = 1; i < iPos - 1; ++i)
            temp = temp->next;

        nodeSC<T>* target = temp->next;
        temp->next = target->next;
        delete target;
        --iCount;
    }
};

// ============================================================
// 5. STACK (LIFO: LAST IN, FIRST OUT)
// ============================================================

template <class T>
struct nodeStack
{
    T data;
    nodeStack<T>* next;
};

template <class T>
class Stack
{
private:
    nodeStack<T>* First;
    int iCount;

public:
    Stack() : First(nullptr), iCount(0) {}

    ~Stack()
    {
        while (First != nullptr)
        {
            nodeStack<T>* temp = First;
            First = First->next;
            delete temp;
        }
    }

    Stack(const Stack&) = delete;
    Stack& operator=(const Stack&) = delete;

    void Push(T No)
    {
        First = new nodeStack<T>{No, First};
        ++iCount;
    }

    void Pop()
    {
        if (First == nullptr)
        {
            std::cout << "Stack is empty\n";
            return;
        }

        nodeStack<T>* temp = First;
        std::cout << "Popped element: " << temp->data << '\n';
        First = First->next;
        delete temp;
        --iCount;
    }

    void Display() const
    {
        nodeStack<T>* temp = First;
        std::cout << "TOP -> ";
        while (temp != nullptr)
        {
            std::cout << "| " << temp->data << " | -> ";
            temp = temp->next;
        }
        std::cout << "NULL\n";
    }

    int Count() const { return iCount; }

    bool IsEmpty() const { return First == nullptr; }
};

// ============================================================
// 6. QUEUE (FIFO: FIRST IN, FIRST OUT)
// ============================================================

template <class T>
struct nodeQueue
{
    T data;
    nodeQueue<T>* next;
};

template <class T>
class Queue
{
private:
    nodeQueue<T>* First;
    nodeQueue<T>* Last;
    int iCount;

public:
    Queue() : First(nullptr), Last(nullptr), iCount(0) {}

    ~Queue()
    {
        while (First != nullptr)
        {
            nodeQueue<T>* temp = First;
            First = First->next;
            delete temp;
        }
        Last = nullptr;
    }

    Queue(const Queue&) = delete;
    Queue& operator=(const Queue&) = delete;

    void Enqueue(T No)
    {
        nodeQueue<T>* newn = new nodeQueue<T>{No, nullptr};

        if (First == nullptr)
            First = Last = newn;
        else
        {
            Last->next = newn;
            Last = newn;
        }
        ++iCount;
    }

    void Dequeue()
    {
        if (First == nullptr)
        {
            std::cout << "Queue is empty\n";
            return;
        }

        nodeQueue<T>* temp = First;
        std::cout << "Dequeued element: " << temp->data << '\n';
        First = First->next;
        delete temp;
        --iCount;

        if (First == nullptr)
            Last = nullptr;
    }

    void Display() const
    {
        nodeQueue<T>* temp = First;
        std::cout << "FRONT -> ";
        while (temp != nullptr)
        {
            std::cout << "| " << temp->data << " | -> ";
            temp = temp->next;
        }
        std::cout << "NULL <- REAR\n";
    }

    int Count() const { return iCount; }

    bool IsEmpty() const { return First == nullptr; }
};


//=====================================================================
//
//                  SECTION 7 : DYNAMIC ARRAY
//
//=====================================================================

template <class T>
class Array
{
private:
    std::vector<T> elements;

public:
    Array() = default;
    explicit Array(std::size_t size) : elements(size) {}

    std::size_t Size() const { return elements.size(); }
    bool IsEmpty() const { return elements.empty(); }

    T& operator[](std::size_t index) { return elements.at(index); }
    const T& operator[](std::size_t index) const { return elements.at(index); }

    void PushBack(const T& value) { elements.push_back(value); }
    void Clear() { elements.clear(); }

    void Accept()
    {
        for (std::size_t i = 0; i < elements.size(); ++i)
        {
            std::cout << "Enter element " << i + 1 << ": ";
            std::cin >> elements[i];
        }
    }

    void Display() const
    {
        for (const T& value : elements) std::cout << value << "\t";
        std::cout << '\n';
    }

    std::vector<T>& Data() { return elements; }
    const std::vector<T>& Data() const { return elements; }
};


//=====================================================================
//
//                  SECTION 8 : SEARCHING ALGORITHMS
//
//=====================================================================

// Returns the first matching zero-based index, or -1 if not found.
template <class T>
int LinearSearch(const std::vector<T>& values, const T& target)
{
    for (std::size_t i = 0; i < values.size(); ++i)
        if (values[i] == target) return static_cast<int>(i);
    return -1;
}

// Checks both ends while moving toward the centre.
template <class T>
int BiDirectionalSearch(const std::vector<T>& values, const T& target)
{
    if (values.empty()) return -1;

    std::size_t left = 0;
    std::size_t right = values.size() - 1;

    while (left <= right)
    {
        if (values[left] == target) return static_cast<int>(left);
        if (values[right] == target) return static_cast<int>(right);
        ++left;
        if (right == 0) break;
        --right;
    }
    return -1;
}

// The input must be sorted in ascending order.
template <class T>
int BinarySearch(const std::vector<T>& values, const T& target)
{
    std::size_t left = 0;
    std::size_t right = values.size();

    while (left < right)
    {
        const std::size_t middle = left + (right - left) / 2;

        if (values[middle] == target) return static_cast<int>(middle);
        if (target < values[middle]) right = middle;
        else left = middle + 1;
    }
    return -1;
}


//=====================================================================
//
//                  SECTION 9 : SORTING ALGORITHMS
//
//=====================================================================

template <class T>
void BubbleSort(std::vector<T>& values)
{
    for (std::size_t pass = 0; pass + 1 < values.size(); ++pass)
        for (std::size_t j = 0; j + 1 < values.size() - pass; ++j)
            if (values[j] > values[j + 1])
                std::swap(values[j], values[j + 1]);
}

template <class T>
void BubbleSortEfficient(std::vector<T>& values)
{
    for (std::size_t pass = 0; pass + 1 < values.size(); ++pass)
    {
        bool swapped = false;
        for (std::size_t j = 0; j + 1 < values.size() - pass; ++j)
        {
            if (values[j] > values[j + 1])
            {
                std::swap(values[j], values[j + 1]);
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

template <class T>
void SelectionSort(std::vector<T>& values)
{
    for (std::size_t i = 0; i + 1 < values.size(); ++i)
    {
        std::size_t minimum = i;
        for (std::size_t j = i + 1; j < values.size(); ++j)
            if (values[j] < values[minimum]) minimum = j;
        if (minimum != i) std::swap(values[i], values[minimum]);
    }
}

template <class T>
void InsertionSort(std::vector<T>& values)
{
    for (std::size_t i = 1; i < values.size(); ++i)
    {
        T selected = values[i];
        std::size_t j = i;
        while (j > 0 && values[j - 1] > selected)
        {
            values[j] = values[j - 1];
            --j;
        }
        values[j] = selected;
    }
}

template <class T>
void Display(const std::vector<T>& values)
{
    for (const T& value : values) std::cout << value << "\t";
    std::cout << '\n';
}


//=====================================================================
//
//                  SECTION 10 : BINARY SEARCH TREE
//
//=====================================================================

template <class T>
class BinarySearchTree
{
private:
    struct TreeNode
    {
        T data;
        TreeNode* left;
        TreeNode* right;

        explicit TreeNode(const T& value) : data(value), left(nullptr), right(nullptr) {}
    };

    TreeNode* root = nullptr;

    static void Clear(TreeNode* node)
    {
        if (node == nullptr) return;
        Clear(node->left);
        Clear(node->right);
        delete node;
    }

    static void InorderImpl(TreeNode* node)
    {
        if (node == nullptr) return;
        InorderImpl(node->left);
        std::cout << node->data << '\t';
        InorderImpl(node->right);
    }

    static void PreorderImpl(TreeNode* node)
    {
        if (node == nullptr) return;
        std::cout << node->data << '\t';
        PreorderImpl(node->left);
        PreorderImpl(node->right);
    }

    static void PostorderImpl(TreeNode* node)
    {
        if (node == nullptr) return;
        PostorderImpl(node->left);
        PostorderImpl(node->right);
        std::cout << node->data << '\t';
    }

    static int CountAllImpl(const TreeNode* node)
    {
        return node == nullptr ? 0 :
            1 + CountAllImpl(node->left) + CountAllImpl(node->right);
    }

    static int CountLeafImpl(const TreeNode* node)
    {
        if (node == nullptr) return 0;
        if (node->left == nullptr && node->right == nullptr) return 1;
        return CountLeafImpl(node->left) + CountLeafImpl(node->right);
    }

    static int CountParentImpl(const TreeNode* node)
    {
        if (node == nullptr) return 0;
        const int isParent = (node->left != nullptr || node->right != nullptr) ? 1 : 0;
        return isParent + CountParentImpl(node->left) + CountParentImpl(node->right);
    }

public:
    BinarySearchTree() = default;
    ~BinarySearchTree() { Clear(root); }

    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;

    // Duplicate values are ignored. Returns true only when inserted.
    bool Insert(const T& value)
    {
        if (root == nullptr)
        {
            root = new TreeNode(value);
            return true;
        }

        TreeNode* current = root;
        while (true)
        {
            if (value == current->data) return false;
            if (value < current->data)
            {
                if (current->left == nullptr)
                {
                    current->left = new TreeNode(value);
                    return true;
                }
                current = current->left;
            }
            else
            {
                if (current->right == nullptr)
                {
                    current->right = new TreeNode(value);
                    return true;
                }
                current = current->right;
            }
        }
    }

    bool Search(const T& value) const
    {
        TreeNode* current = root;
        while (current != nullptr)
        {
            if (value == current->data) return true;
            current = (value < current->data) ? current->left : current->right;
        }
        return false;
    }

    void Inorder() const { InorderImpl(root); std::cout << '\n'; }
    void Preorder() const { PreorderImpl(root); std::cout << '\n'; }
    void Postorder() const { PostorderImpl(root); std::cout << '\n'; }

    int CountLeaf() const { return CountLeafImpl(root); }
    int CountParent() const { return CountParentImpl(root); }
    int CountAll() const { return CountAllImpl(root); }
    bool IsEmpty() const { return root == nullptr; }
};

} // namespace GDSL

#endif // GDSL_H
