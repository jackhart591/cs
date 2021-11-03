#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "dynarray.h"

 /*
 * Name: Jackson Hart
 * Email: hartjack@oregonstate.edu
 */

#define INIT_CAPACITY 2

struct dynarray* dynarray_create() {
  struct dynarray* temp = malloc(sizeof(struct dynarray));
  temp->data = malloc(INIT_CAPACITY * sizeof(void*));
  temp->capacity = INIT_CAPACITY; 
  temp->size = 0;
  temp->start = 0;
  return temp;
}

void dynarray_free(struct dynarray* da) {
  free(da->data);
  free(da);
}

int dynarray_size(struct dynarray* da) { return da->size; }

int dynarray_capacity(struct dynarray* da) { return da->capacity; }

void dynarray_resize(struct dynarray* da, int new_capacity) {
  void** temp = malloc(new_capacity * sizeof(void*));

  for(int i = 0; i < da->size; i++) {
    temp[i] = da->data[dynarray_logical_index(da, i)];
  }

  free(da->data);
  da->data = temp;
  da->capacity = new_capacity;
  da->start = 0;
}

void dynarray_insert(struct dynarray* da, void* val) {
  if (da->size == da->capacity) {
    da->data = realloc(da->data, (da->capacity * 2) * sizeof(void*));
    da->capacity *= 2;
  }

  da->data[da->size] = val;
  da->size++;
}

int dynarray_logical_index(struct dynarray* da, int idx) { return ((da->start + idx) % da->capacity); }

void dynarray_remove(struct dynarray* da, int idx) {
  for (int i = idx+1; i < da->size; i++) {
    da->data[i-1] = da->data[i];
  }

  da->size--;
}

void* dynarray_get(struct dynarray* da, int idx) { return da->data[idx]; }

void dynarray_set(struct dynarray* da, int idx, void* val) { da->data[idx] = val; }