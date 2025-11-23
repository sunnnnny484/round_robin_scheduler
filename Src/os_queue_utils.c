/*
 * os_queue_utils.h
 *
 *  Created on: Nov 23, 2025
 *      Author: khaidq
 */

#include <stdlib.h>
#include <stdint.h>
#include <os_queue_utils.h>

static void swap(TCB_t **a, TCB_t **b) {
    TCB_t *tmp = *a;
    *a = *b;
    *b = tmp;
}

static void heapify_up(MaxHeap *heap, int index) {
    while (index > 0) {
        int parent = (index - 1) / 2;

        if (heap->nodes[index]->priority > heap->nodes[parent]->priority) {
            swap(&heap->nodes[index], &heap->nodes[parent]);
            index = parent;
        } else {
            break;
        }
    }
}

static void heapify_down(MaxHeap *heap, int index) {
    while (1) {
        int left  = index * 2 + 1;
        int right = index * 2 + 2;
        int largest = index;

        if (left < heap->size && heap->nodes[left]->priority > heap->nodes[largest]->priority)
            largest = left;

        if (right < heap->size && heap->nodes[right]->priority > heap->nodes[largest]->priority)
            largest = right;

        if (largest != index) {
            swap(&heap->nodes[index], &heap->nodes[largest]);
            index = largest;
        } else {
            break;
        }
    }
}

void OsHeapInit(MaxHeap *heap) {
    heap->size = 0;
}

int32_t OsHeapInsert(MaxHeap *heap, TCB_t *task) {
    if (heap->size >= MAX_TASKS)
        return -1;   // full

    heap->nodes[heap->size] = task;
    heapify_up(heap, heap->size);
    heap->size++;
    return 0;
}

TCB_t* OsHeapPeek(MaxHeap *heap) {
    if (heap->size == 0)
        return NULL;
    return heap->nodes[0];
}

TCB_t* OsHeapExtract(MaxHeap *heap) {
    if (heap->size == 0)
        return NULL;

    TCB_t *top = heap->nodes[0];

    heap->size--;
    heap->nodes[0] = heap->nodes[heap->size];
    heapify_down(heap, 0);

    return top;
}
