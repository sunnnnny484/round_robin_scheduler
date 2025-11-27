/*
 * os_blocked_queue.c
 *
 *  Created on: Nov 23, 2025
 *      Author: khaidq
 */

#include <stdint.h>
#include <stdlib.h>
#include <os_blocked_queue.h>

static void swap(TCB_t **a, TCB_t **b) {
    TCB_t *tmp = *a;
    *a = *b;
    *b = tmp;
}

static void heapify_up(MinHeap *heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;

        if (heap->nodes[index]->block_count < heap->nodes[parent]->block_count) {
            swap(&heap->nodes[index], &heap->nodes[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

static void heapify_down(MinHeap *heap, int index) {
    while (1) {
        int left  = index * 2 + 1;
        int right = index * 2 + 2;
        int smallest = index;

        if (left < heap->size &&
            heap->nodes[left]->block_count < heap->nodes[smallest]->block_count)
            smallest = left;

        if (right < heap->size &&
            heap->nodes[right]->block_count < heap->nodes[smallest]->block_count)
            smallest = right;

        if (smallest != index) {
            swap(&heap->nodes[index], &heap->nodes[smallest]);
            index = smallest;
        } else {
            break;
        }
    }
}

void OsMinHeapInit(MinHeap *heap) {
    heap->size = 0;
}

int32_t OsMinHeapInsert(MinHeap *heap, TCB_t *task) {
    if (heap->size >= MAX_TASKS)
        return -1;

    heap->nodes[heap->size] = task;
    heapify_up(heap, heap->size);
    heap->size++;
    return 0;
}

TCB_t* OsMinHeapPeek(MinHeap *heap) {
    if (heap->size == 0)
        return NULL;
    return heap->nodes[0];
}

TCB_t* OsMinHeapExtract(MinHeap *heap) {
    if (heap->size == 0)
        return NULL;

    TCB_t *top = heap->nodes[0];

    heap->size--;
    heap->nodes[0] = heap->nodes[heap->size];
    heapify_down(heap, 0);

    return top;
}


