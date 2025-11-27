/*
 * os_blocked_queue.h
 *
 *  Created on: Nov 23, 2025
 *      Author: khaidq
 */

#ifndef OS_BLOCKED_QUEUE_H_
#define OS_BLOCKED_QUEUE_H_

#include <os_kernel.h>

typedef struct {
    TCB_t *nodes[MAX_TASKS];
    int size;
} MinHeap;

void OsMinHeapInit(MinHeap *heap);
int32_t OsMinHeapInsert(MinHeap *heap, TCB_t *task);
TCB_t* OsMinHeapPeek(MinHeap *heap);
TCB_t* OsMinHeapExtract(MinHeap *heap);

#endif /* OS_BLOCKED_QUEUE_H_ */
