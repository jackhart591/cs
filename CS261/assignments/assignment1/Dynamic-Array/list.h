#ifndef __LIST_H
#define __LIST_H

struct list;

struct list* list_create();
void list_free(struct list* list);
void list_insert(struct list* list, void* val);
void list_remove(struct list* list, void* val, int (*cmp)(void* a, void* b));
int list_position(struct list* list, void* val, int (*cmp)(void* a, void* b));
void list_reverse(struct list* list);

#endif