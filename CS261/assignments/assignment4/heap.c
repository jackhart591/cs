#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "heap.h"
#include "dynarray.h"

struct node {
    int key;
    void* value;
};

struct heap {
    struct dynarray* nodes;
};

struct heap* heap_create() {
    struct heap* temp = malloc(sizeof(struct heap));
    temp->nodes = dynarray_create();

    return temp;
}

int heap_get_parent_idx(struct heap* heap, int idx) {
    assert(heap != NULL);

    int parent_idx = (idx - 1) / 2;
    if (parent_idx >= 0 && idx != 0) {
        return parent_idx;
    } else { return -1; }
}

int heap_get_left_child_idx(struct heap* heap, int idx) {
    assert(heap != NULL);
    int left_child_idx = (2 * idx) + 1;
    
    if (left_child_idx >= dynarray_size(heap->nodes)-1) {
        return -1;
    }

    return left_child_idx;
}

int heap_get_right_child_idx(struct heap* heap, int idx) {
    assert(heap != NULL);
    int right_child_idx = (2* idx) + 2;
    
    if (right_child_idx >= dynarray_size(heap->nodes)-1) {
        return -1;
    }

    return right_child_idx;
}

void heap_percolate_up(struct heap* heap, int idx) {
    int parent_idx = heap_get_parent_idx(heap, idx);

    if (parent_idx == -1) {
        return;
    }

    struct node* parent = (struct node*) dynarray_get(heap->nodes, parent_idx);
    struct node* node = (struct node*) dynarray_get(heap->nodes, idx);

    if (parent->key > node->key) {
        dynarray_swap(heap->nodes, parent_idx, idx);
        heap_percolate_up(heap, parent_idx);
    }
}

void heap_percolate_down(struct heap* heap, int idx) {
    int left_child_idx = heap_get_left_child_idx(heap, idx);
    int right_child_idx = heap_get_right_child_idx(heap, idx);
    int min_child;

    if (left_child_idx != -1 || right_child_idx != -1) {
        if (left_child_idx != -1 && right_child_idx != -1) {
            struct node* left_child = (struct node*) dynarray_get(heap->nodes, left_child_idx);
            struct node* right_child = (struct node*) dynarray_get(heap->nodes, right_child_idx);
            if (left_child->key >= right_child->key) {
                min_child = right_child_idx;
            } else { min_child = left_child_idx; }
        } else if (left_child_idx != -1) {
            min_child = left_child_idx;
        } else {
            min_child = right_child_idx;
        }

        struct node* child = (struct node*) dynarray_get(heap->nodes, min_child);
        struct node* node = (struct node*) dynarray_get(heap->nodes, idx);

        if (node->key >= child->key) {
            dynarray_swap(heap->nodes, idx, min_child);
            heap_percolate_down(heap, min_child);
        }
    } else { return; }
}

void* heap_remove(struct heap* heap, int idx) {
    assert(heap != NULL);
    struct node* removeNode = (struct node*) dynarray_get(heap->nodes, idx);
    void* value = removeNode->value;

    dynarray_set(heap->nodes, idx, dynarray_get(heap->nodes, dynarray_size(heap->nodes) - 1));
    heap_percolate_down(heap, idx);
    dynarray_remove(heap->nodes, dynarray_size(heap->nodes) - 1);

    free(removeNode);

    return value;
}

void heap_insert(struct heap* heap, int key, void* value) {
    assert(heap != NULL);

    struct node* new_node = malloc(sizeof(struct node));
    new_node->key = key;
    new_node->value = value;

    dynarray_insert(heap->nodes, new_node);
    heap_percolate_up(heap, dynarray_size(heap->nodes) - 1);

}

void heap_print(struct heap* heap) {
    assert(heap != NULL);

    for(int i = 0; i < dynarray_size(heap->nodes); i++) {
        struct node* currentNode = (struct node*) dynarray_get(heap->nodes, i);
        printf("Value %d - Key: %d \n", i, currentNode->key);
    }
}

int heap_isempty(struct heap* heap) {
    assert (heap != NULL);

    if (dynarray_size(heap->nodes) == 0) {
        return 1;
    } else { return 0; }
}

int heap_get_key(struct heap* heap, int idx) {
    assert(heap != NULL);

    struct node* currentNode = (struct node*) dynarray_get(heap->nodes, idx);

    return currentNode->key;
}

void* heap_get_val(struct heap* heap, int idx) {
    assert(heap != NULL);

    struct node* currentNode = (struct node*) dynarray_get(heap->nodes, idx);

    return currentNode->value;
}

void heap_free(struct heap* heap) {
    assert(heap != NULL);

    dynarray_free(heap->nodes);
    free(heap);

    heap = NULL;
}