#include <stdlib.h>
#include <stdio.h>
#include "dynarray.h"
#include "list.h"

int cmp(void* a, void* b) {
    if(a == b) {
        return 0;
    } else { return 1; }
}


int main() {

    struct list* listboi = list_create();

    list_insert(listboi, (int*)69);
    list_insert(listboi, (int*)70);
    list_insert(listboi, (int*)71);

    list_remove(listboi, (int*)69, cmp);
    list_print(listboi);

    list_insert(listboi, (int*)72);
    list_insert(listboi, (int*)55);
    list_insert(listboi, (int*)69);

    list_print(listboi);

    printf("Found 55 at position %d\n", list_position(listboi, (int*)55, cmp));

    list_free(listboi);

    return 0;
}