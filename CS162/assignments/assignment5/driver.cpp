#include "Linked_List.h"

int main() {
    Linked_List<int> list;

    list.PushFront(2);
    list.PushFront(4);
    list.PushFront(2054);

    list.Print();

    return 0;
}