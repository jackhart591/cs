/*
 * Name: Jackson Hart
 * Email: hartjack@oregonstate.edu
 */

#include <stdlib.h>
#include "queue.h"
#include "dynarray.h"

struct queue {
  struct dynarray* array;
};

struct queue* queue_create() {
  struct queue* temp = malloc(sizeof(struct queue));
  temp->array = dynarray_create();

  return temp;
}

void queue_free(struct queue* queue) {
  dynarray_free(queue->array);
  free(queue);
}

int queue_isempty(struct queue* queue) {
  if(dynarray_size(queue->array) == 0) {
    return 1;
  } else { return 0; }
}

void queue_enqueue(struct queue* queue, void* val) {
  if(queue->array->size == queue->array->capacity) {
    dynarray_resize(queue->array, 2 * queue->array->capacity);
  }

  queue->array->data[dynarray_logical_index(queue->array, queue->array->size)] = val;
  queue->array->size++;
}

void* queue_front(struct queue* queue) {
  return dynarray_get(queue->array, queue->array->start);
}

void* queue_dequeue(struct queue* queue) {
  void* value = dynarray_get(queue->array, queue->array->start);
  queue->array->size--;

  if(queue->array->size > 0 && queue->array->size != 1) {
    queue->array->start = dynarray_logical_index(queue->array, 1);
  }

  return value;
}