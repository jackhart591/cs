#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "dynarray.h"

 /*
 * Name: Jackson Hart
 * Email: hartjack@oregonstate.edu
 */

struct dynarray* dynarray_create() {
  struct dynarray* temp = malloc(sizeof(struct dynarray));
  temp->data = malloc(2 * sizeof(void*));
  temp->capacity = 2; 
  temp->size = 0;
  return temp;
}

void dynarray_free(struct dynarray* da) {
  assert(da != NULL);
  free(da->data);
  free(da);
}

int dynarray_size(struct dynarray* da) { 
  assert(da != NULL);
  return da->size; 
}

int dynarray_capacity(struct dynarray* da) { 
  assert(da != NULL);
  return da->capacity; 
}

void dynarray_insert(struct dynarray* da, void* val) {
  assert(da != NULL && val != NULL);

  if (da->size == da->capacity) {
    da->data = realloc(da->data, (da->capacity * 2) * sizeof(void*));
    da->capacity *= 2;
  }

  da->data[da->size] = val;
  da->size++;
}

void dynarray_remove(struct dynarray* da, int idx) {
  assert(da != NULL && da->size <= idx && idx >= 0);

  for (int i = idx+1; i < da->size; i++) {
    da->data[i-1] = da->data[i];
  }

  da->size--;
}

void* dynarray_get(struct dynarray* da, int idx) { 
  assert(da != NULL);
  assert(da->size <= idx && idx >= 0);
  return da->data[idx]; 
}

void dynarray_set(struct dynarray* da, int idx, void* val) { 
  assert(da != NULL);
  assert(da->size <= idx && idx >= 0);
  
  da->data[idx] = val; 
}