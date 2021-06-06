#include <iostream>
#include "Linked_List.h"
#include <iostream>

template <class T>
Linked_List<T>::Linked_List() {
    this->length = 0;
}

template <class T>
Linked_List<T>::~Linked_List() {
    Node<T>* next = this->head;
    for (int i = 0; i < this->length; i++) {
        Node<T>* current = next;
        next = current->next;
        delete current;
    }

    this->length = 0;
}

template <class T>
unsigned int Linked_List<T>::PushFront(T val) {
    Node<T>* temp = new Node<T>(val);
    if (this->length > 0) { // if list already exists
        temp->next = this->head;
        this->head = temp;
    } else { // initialize
        this->head = temp;
        this->foot = temp;
    }

    return ++this->length;
}

template <class T>
unsigned int Linked_List<T>::PushBack(T val) {
    Node<T>* temp = new Node<T>(val);
    if (this->length > 0) { // if list already exists
        this->foot->next = temp;
        this->foot = temp;
    } else { // initialize
        this->head = temp;
        this->foot = temp;
    }

    return ++this->length;
}

template <class T>
unsigned int Linked_List<T>::Insert(unsigned int pos, T val) {
    Node<T>* temp = new Node<T>(val);
    if (this->length < pos || pos < 0) { // out of bounds
        throw pos;
    } else if (this->length > 0) {
        Node<T>* next = this->head;
        for (int i = 0; i < pos-1; i++) { // get into position
            next = next->next;
        }

        temp->next = next->next;
        next->next = temp;
    } else { // when list hasn't been initialized yet
        this->head = temp;
        this->foot = temp;
    }

    return ++this->length;
}

template <class T>
void Linked_List<T>::Clear() {
    Node<T>* next = this->head;
    for (int i = 0; i < this->length; i++) {
        Node<T>* current = next;
        next = current->next;
        delete current;
    }

    this->length = 0;
}

template <class T>
void Linked_List<T>::Print() {
    Node<T>* next = this->head;
    for (int i = 0; i < this->length; i++) {
        std::cout << "Value at position " << i+1 << ": ";
        std::cout << next->val << std::endl;
        next = next->next;
    }
}

template <class T>
void Linked_List<T>::SortDescending() {
    Node<T>* current = this->head;
    Node<T>* max = new Node<T>(0);
    Node<T>* maxPtr = max;
    max->next = this->head;

    int pos = 0;
    for (int i = 0; i < this->length-1; i++) { // find current max value in list
        if (current->next->val > max->next->val) {
            max = current;
        }
        current = current->next;
    }

    if (max->next != this->head) {
        current = max->next->next; //swap
        max->next->next = this->head;
        this->head = max->next;
        max->next = current;
    }

    this->SortDescending(++pos, this->head); // call for next position
    delete maxPtr;
}

template <class T>
void Linked_List<T>::SortDescending(int& pos, Node<T>* start) {
    Node<T>* current = start->next;
    Node<T>* max = start;
    if (pos < this->length) {
        for (int i = pos; i < this->length-1; i++) { // iterate through remaining list
            if (current->next->val > max->next->val) {
                max = current;
            }
            current = current->next; // put sorted value into position
        }

        if (max != start) {
            current = max->next->next; //swap
            max->next->next = start->next;
            start->next = max->next;
            max->next = current;
        }

        this->SortDescending(++pos, start->next); // call for next position
    } else { return; }
}

template class Linked_List<int>;
template class Linked_List<unsigned int>;