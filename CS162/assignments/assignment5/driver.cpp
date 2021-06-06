#include <iostream>
#include "Linked_List.h"

int main() {
    try {
        Linked_List<int> list;

        list.PushFront(2);
        list.PushFront(4);
        list.PushFront(2054);
        list.PushBack(23430);
        list.PushBack(69);

        list.Print();
        std::cout << std::endl;
        list.SortDescending();
        list.Print();
    } catch (int x) {

    }

    return 0;
}