#pragma once
#include "Node.h"

template <typename T>
class Linked_List {
private:
    unsigned int length;
    Node<T>* head;
    Node<T>* foot;

public:
    Linked_List();
    ~Linked_List();
    Linked_List& operator=(const Linked_List&);

    unsigned int GetLength() { return length; };
    void Print();
    //void Clear();
    unsigned int PushFront(T);
    //unsigned int PushBack(T);
    //unsigned int Insert(int, unsigned int);
    //void SortAscending();
    //void SortDescending();
};