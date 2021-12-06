#ifndef __HEAP_H
#define __HEAP_H

struct heap;

struct heap* heap_create();
void heap_insert(struct heap* heap, int key, void* value);
void* heap_remove(struct heap* heap, int idx);
void heap_print(struct heap* heap);
int heap_isempty(struct heap* heap);
void* heap_get_val(struct heap* heap, int idx);
int heap_get_key(struct heap* heap, int idx);
void heap_free(struct heap* heap);

#endif