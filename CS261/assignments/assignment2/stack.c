/*
 * Name: Jackson Hart
 * Email: hartjack@oregonstate.edu
 */

#include <stdlib.h>
#include "stack.h"
#include "list.h"

struct stack {
  struct list* list;
};

struct stack* stack_create() {
  struct stack* temp = malloc(sizeof(struct stack));
  temp->list = list_create();

  return temp;
}

void stack_free(struct stack* stack) {
  list_free(stack->list);
  free(stack);
}

int stack_isempty(struct stack* stack) {
  if (stack->list->head == NULL) {
    return 1;
  } else { return 0; }
}

void stack_push(struct stack* stack, void* val) {
  list_insert(stack->list, val);
}

void* stack_top(struct stack* stack) {
  return stack->list->head->val;
}

void* stack_pop(struct stack* stack) {
  struct link* it = stack->list->head;

  stack->list->head = it->next;
  void* temp = it->val;
  free(it);

  return temp;
}