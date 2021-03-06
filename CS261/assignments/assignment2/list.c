#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "list.h"

 /*
 * Name: Jackson Hart
 * Email: hartjack@oregonstate.edu
 */

struct list* list_create() {
  struct list* temp = malloc(sizeof(struct list));
  temp->head = NULL;
  return temp;
}

void list_free(struct list* list) {
  struct link* it = list->head;
  while (it != NULL) {
    struct link* next = it->next;
    free(it);
    it = next;
  }

  free(list);
}

void list_insert(struct list* list, void* val) {
  struct link* new_link = malloc(sizeof(struct link));
  new_link->val = val;
  new_link->next = NULL;

  if (list->head != NULL) {
    struct link* temp = list->head;
    list->head = new_link;
    new_link->next = temp;
  } else {
    list->head = new_link;
  }
}

void list_print(struct list* list) {
  struct link* it = list->head;
  
  for(int i = 0; it != NULL; i++) {
    printf("Node %d: %d\n", i+1, it->val);
    it = it->next;
  }
}

void list_remove(struct list* list, void* val, int (*cmp)(void* a, void* b)) {
  struct link* it = list->head;
  struct link* before = NULL;

  for(int i = 0; it != NULL; i++) {
    if (cmp(it->val, val) == 0) {
      struct link* next = it->next;
      free(it);
      if (i == 0) list->head = next;
      else before->next = next;
      return;
    } else {
      before = it;
      it = it->next;
    }
  }
}

int list_position(struct list* list, void* val, int (*cmp)(void* a, void* b)) {
  struct link* it = list->head;
  int i;
  int foundNum = -1;
  for(i = 0; it != NULL; i++) {
    if(cmp(it->val, val) == 0) {
      return i;
    }
    it = it->next;
  }

  return foundNum;
}

void list_reverse(struct list* list) {
  struct link* it = list->head;
  struct link* before = NULL;

  for (int i = 0; it != NULL; i++) {
    struct link* next = it->next;
    it->next = before;
    before = it;
    it = next;
  }

  list->head = before;
}