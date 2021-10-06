#ifndef DYNARRAY
#define DYNARRAY

struct dynarray {
    void* arr;
    int cache;
    int size;
};

struct dynarray* dynarray_create(int size);
void dynarray_free(struct dynarray* arr);
void dynarray_size(struct dynarray* arr);
void dynarray_insert(struct dynarray* arr);
void dynarray_remove(struct dynarray* arr);
void dynarray_get(struct dynarray* arr, int index);
void dynarray_set(struct dynarray* arr, int index);


#endif