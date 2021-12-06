/*
 * Name: Jackson Hart
 * Email: hartjack@oregonstate.edu
 */

#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

#include "pq.h"
#include "heap.h"

struct pq {
    struct heap* heap;
};

struct pq* pq_create() {
    struct pq* pq = malloc(sizeof(struct pq));
    pq->heap = heap_create();

    return pq;
}

void pq_free(struct pq* pq) {
    assert(pq != NULL);

    heap_free(pq->heap);
    free(pq);

    pq = NULL;
}

int pq_isempty(struct pq* pq) {
    assert(pq != NULL);

    return heap_isempty(pq->heap);
}

void pq_insert(struct pq* pq, void* value, int priority) {
    assert(pq != NULL);

	heap_insert(pq->heap, priority, value);
}

void* pq_first(struct pq* pq) {
    assert(pq != NULL);

    return heap_get_val(pq->heap, 0);
}

int pq_first_priority(struct pq* pq) {
    assert(pq != NULL);

    return heap_get_key(pq->heap, 0);
}

void* pq_remove_first(struct pq* pq) {
    return heap_remove(pq->heap, 0);
}