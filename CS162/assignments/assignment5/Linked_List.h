#pragma once
#include "Node.h"

template <typename T>
class Linked_List {
private:
    unsigned int length;
    Node<T>* head;
    Node<T>* foot;

    void SortDescending(unsigned int&, Node<T>*);
    Node<T>* SortAscending(Node<T>*, unsigned int);

public:
    Linked_List();
    ~Linked_List();

    unsigned int GetLength() { return length; };
    void Print();
    void Clear();
    unsigned int PushFront(T);
    unsigned int PushBack(T);
    unsigned int Insert(unsigned int, T);
    void SortAscending();
    void SortDescending();
    int FindNumPrimes();
};