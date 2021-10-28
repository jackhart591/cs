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

void queue_enqueue(struct queue* queue, void* val) { // circular enqueueing dumbass
  dynarray_insert(queue->array, val);
}

void* queue_front(struct queue* queue) {
  return dynarray_get(queue->array, 0);
}

/*
 * This function should dequeue a value from a given queue and return the
 * dequeued value.  This function must have O(1) average runtime complexity.
 *
 * Params:
 *   queue - the queue from which a value is to be dequeued.  May not be NULL.
 *
 * Return:
 *   This function should return the value that was dequeued.
 */
void* queue_dequeue(struct queue* queue) {

}