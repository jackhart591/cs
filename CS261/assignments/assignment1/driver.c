#include <stdlib.h>
#include <stdio.h>
#include "dynarray.h"
#include "list.h"


int main() {

    struct dynarray* mamamia = dynarray_create();

    dynarray_insert(mamamia, (int*)69);
    dynarray_insert(mamamia, (int*)70);
    dynarray_insert(mamamia, (int*)71);
    printf("Capacity: %d\n", mamamia->capacity);
    printf("Size: %d\n", dynarray_size(mamamia));

    dynarray_remove(mamamia, 1);
    printf("Element 0: %d\n", dynarray_get(mamamia, 0));
    printf("Element 1: %d\n", dynarray_get(mamamia, 1));

    dynarray_free(mamamia);

    return 0;
}