/*
 * os_semaphore.c
 *
 *  Created on: Feb 26, 2026
 *      Author: khaidq
 */

#include <stdint.h>
#include <os_semaphore.h>
#include <os_queue_utils.h>   /* OsHeapExtract, OsHeapInsert */

extern MaxHeap    taskQueue;
extern TCB_t     *currentTask;
extern void       yield(void);

static void sem_enqueue(OsSemaphore_t *sem, TCB_t *task) {
    if (sem->size >= MAX_TASKS)
        return;

    sem->waitQueue[sem->tail] = task;
    sem->tail = (sem->tail + 1) % MAX_TASKS;
    sem->size++;
}

static TCB_t* sem_dequeue(OsSemaphore_t *sem) {
    if (sem->size == 0)
        return NULL;

    TCB_t *task = sem->waitQueue[sem->head];
    sem->head = (sem->head + 1) % MAX_TASKS;
    sem->size--;
    return task;
}

void OsSemInit(OsSemaphore_t *sem, int32_t count) {
    sem->count = count;
    sem->head  = 0;
    sem->tail  = 0;
    sem->size  = 0;
}

void OsSemWait(OsSemaphore_t *sem) {
    sem->count--;

    if (sem->count < 0) {
        TCB_t *task = OsHeapExtract(&taskQueue);
        task->current_state = SEM_BLOCKED_STATE;
        sem_enqueue(sem, task);
        yield();
    }
}

void OsSemSignal(OsSemaphore_t *sem) {
    sem->count++;

    if (sem->count <= 0) {
        TCB_t *task = sem_dequeue(sem);
        if (task != NULL) {
            task->current_state = RUNNING_STATE;
            OsHeapInsert(&taskQueue, task);
        }
    }
}
