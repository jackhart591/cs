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
}

template <class T>
Linked_List<T>& Linked_List<T>::operator=(const Linked_List<T>& other) {
    //this->clear();
    
}

template <class T>
unsigned int Linked_List<T>::PushFront(T val) {
    Node<T>* temp = new Node<T>(val);
    if (this->length > 0) {
        temp->next = this->head;
        this->head = temp;
    } else {
        this->head = temp;
        this->foot = temp;
    }

    this->length++;
    return this->length;
}

template <class T>
void Linked_List<T>::Print() {
    Node<T>* next = this->head;
    for (int i = 0; i < this->length; i++) {
        std::cout << "Value at position " << i+1 << ": ";

        Node<T>* current = next;
        next = current->next;

        std::cout << current->val << std::endl;
    }
}

template class Linked_List<int>;
template class Linked_List<unsigned int>;