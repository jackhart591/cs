#include <iostream>
#include "Linked_List.h"
#include <iostream>
#include <cmath>

/*********************************************************************
** Program Filename: Linked_List.cpp
** Author: Jackson Hart
** Date: 6/8/2021
** Description: Implementation of Linked_List class
** Input: none
** Output: none
*********************************************************************/

/*********************************************************************
** Function: Linked_List constructor
** Description: sets length to a default value of 0
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

template <class T>
Linked_List<T>::Linked_List() {
    this->length = 0;
}

/*********************************************************************
** Function: Linked_List deconstructor
** Description: deallocates the list
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

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

/*********************************************************************
** Function: PushFront
** Description: Puts a new node at the head of the list with given
                value
** Parameters: value to be stored in node
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

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

/*********************************************************************
** Function: PushBack
** Description: Puts a new node at the foot of the list with given
                value
** Parameters: value to be stored in node
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

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

/*********************************************************************
** Function: PushFront
** Description: insterts a new node at the given position with the 
                given value
** Parameters: position and value to be stored in node
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

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

/*********************************************************************
** Function: Clear
** Description: Clears the list
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

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

/*********************************************************************
** Function: Print
** Description: Prints the list
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

template <class T>
void Linked_List<T>::Print() {
    Node<T>* next = this->head;
    int i = 1;
    while (next != NULL) {
        std::cout << "Value at position " << i << ": ";
        std::cout << next->val << std::endl;
        next = next->next;
        i++;
    }
}

/*********************************************************************
** Function: SortDescending
** Description: Sorts the list in descending order using a selection
                sort
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

template <class T>
void Linked_List<T>::SortDescending() {
    Node<T>* current = this->head;
    Node<T>* max = new Node<T>(0);
    Node<T>* maxPtr = max;
    max->next = this->head;

    unsigned int pos = 0;
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

/*********************************************************************
** Function: SortDescending
** Description: Sorts the list in descending order using a selection
                sort
** Parameters: starting index and node
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

template <class T>
void Linked_List<T>::SortDescending(unsigned int& pos, Node<T>* start) {
    Node<T>* current = start->next;
    Node<T>* max = start;
    if (pos < this->length) {
        for (unsigned int i = pos; i < this->length-1; i++) { // iterate through remaining list
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

/*********************************************************************
** Function: Merge
** Description: Merges left and right list and returns it
** Parameters: the position, the left list, and the right list
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

template <class T>
Node<T>* Merge(Node<T>* pos, Node<T>* left, Node<T>* right) {
    while (left != NULL || right != NULL) { // sort
        if (left != NULL) {
            if (right != NULL) {
                if (left->val < right->val) {
                    pos->next = left;
                    left = left->next;
                } else {
                    pos->next = right;
                    right = right->next;
                }
            } else {
                pos->next = left;
                left = left->next;
            }
        } else {
            pos->next = right;
            right = right->next;
        }
        pos = pos->next;
    }

    return pos;
}

/*********************************************************************
** Function: SortAscending
** Description: Sorts the list in ascending order using a merge sort
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/ 

template <class T>
void Linked_List<T>::SortAscending() {
    if (this->length > 1) { 
        Node<T>* left = this->head;
        Node<T>* right = this->head;
        for (int i = 0; i < this->length/2; i++) { // split
            right = right->next;
        }

        Node<T>* temp = right->next;
        right->next = NULL;
        right = temp;

        left = SortAscending(left, this->length - (this->length/2));
        right = SortAscending(right, this->length/2);

        if (left->val > right->val) {
            this->head = right;
            right = right->next;
        } else {
            this->head = left;
            left = left->next;
        }

        Node<T>* pos = this->head;
        Merge(pos, left, right);
    }
}

/*********************************************************************
** Function: SortAscending
** Description: Sorts the list in ascending order using a merge sort
** Parameters: starting node and the length of the list
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

template <class T>
Node<T>* Linked_List<T>::SortAscending(Node<T>* start, unsigned int length) {
    Node<T>* left = start;
    Node<T>* right = start;
    Node<T>* pos = start;

    if (length > 1) {
        for (unsigned int i = 0; i < ceil(double(length)/2)-1; i++) { // split
            right = right->next;
        }
        Node<T>* temp = right->next;
        right->next = NULL;
        right = temp;

        left = SortAscending(left, ceil(double(length) / 2));
        right = SortAscending(right, length - ceil((double)length / 2));

        if (left->val > right->val) {
            start = right;
            right = right->next;
        } else {
            start = left;
            left = left->next;
        }

        pos = start;
        Merge(start, left, right);
    } else {
        pos = start;
    }

    return pos;
}

/*********************************************************************
** Function: FindNumPrimes
** Description: Finds the number of primes in the list
** Parameters: none
** Pre-Conditions: none
** Post-Conditions: none
*********************************************************************/

template <class T>
int Linked_List<T>::FindNumPrimes() {
    Node<T>* pos = this->head;
    unsigned int num = 0;
    for (int i = 0; i < this->length; i++) {
        for (unsigned int j = 2; j < pos->val; j++) {
            if (pos->val % j == 0) {
                num++;
                break;
            }
        }
        pos = pos->next;
    }

    return num;
}

template class Linked_List<unsigned int>;
template class Linked_List<int>;