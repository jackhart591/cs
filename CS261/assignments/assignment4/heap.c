#include "heap.h"
#include "dynarray.h"

struct node {
    int key;
    void* value;
};

struct heap {
    struct dynarray nodes;
};

struct heap* heap_create() {
    struct heap* temp = malloc(sizeof(struct heap));
    temp->nodes = dynarray_create();
}

void heap_percolate_up(struct heap* heap, int idx) {
    int parent_idx = (idx - 1) / 2;

    if (dynarray_get(heap->nodes, parent_idx) > dynarray_get(heap->nodes, idx)) {
        // swap then recursively call
    }
}

void heap_insert(struct heap* heap, int key, void* value) {
    assert(heap != NULL);
    assert(key != NULL && value != NULL);

    struct node* new_node = malloc(sizeof(struct node));
    new_node->key = key;
    new_node->value = value;

    dynarray_insert(heap->nodes, new_node);
    heap_percolate_up(heap, heap->nodes->size-1);

}