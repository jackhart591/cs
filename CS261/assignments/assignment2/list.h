#ifndef __LIST_H
#define __LIST_H

struct list {
  struct link* head;
};

struct link {
  void* val;
  struct link* next;
};

struct list* list_create();
void list_free(struct list* list);
void list_insert(struct list* list, void* val);
void list_remove(struct list* list, void* val, int (*cmp)(void* a, void* b));
void* list_remove_first(struct list* list);
int list_position(struct list* list, void* val, int (*cmp)(void* a, void* b));
void list_reverse(struct list* list);
void list_print(struct list* list);

#endif