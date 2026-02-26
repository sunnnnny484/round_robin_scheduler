/*
 * os_semaphore.h
 *
 *  Created on: Feb 26, 2026
 *      Author: khaidq
 */

#ifndef OS_SEMAPHORE_H_
#define OS_SEMAPHORE_H_

#include <stdint.h>
#include <os_kernel.h>
#include <stdlib.h>

typedef struct {
    int32_t  count;
    TCB_t   *waitQueue[MAX_TASKS];
    int      head;
    int      tail;
    int      size;
} OsSemaphore_t;

void OsSemInit(OsSemaphore_t *sem, int32_t count);
void OsSemWait(OsSemaphore_t *sem);
void OsSemSignal(OsSemaphore_t *sem);

#endif /* OS_SEMAPHORE_H_ */
