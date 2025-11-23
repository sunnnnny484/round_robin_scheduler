/*
 * os_queue_utils.h
 *
 *  Created on: Nov 23, 2025
 *      Author: khaidq
 */

#ifndef OS_QUEUE_UTILS_H_
#define OS_QUEUE_UTILS_H_

#include <os_kernel.h>

typedef struct {
    TCB_t *nodes[MAX_TASKS];
    int size;
} MaxHeap;

void OsHeapInit(MaxHeap *heap);
int32_t OsHeapInsert(MaxHeap *heap, TCB_t *task);
TCB_t* OsHeapPeek(MaxHeap *heap);
TCB_t* OsHeapExtract(MaxHeap *heap);

#endif /* OS_QUEUE_UTILS_H_ */
