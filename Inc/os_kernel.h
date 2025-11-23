/*
 * os_kernel.h
 *
 *  Created on: Nov 23, 2025
 *      Author: khaidq
 */

#ifndef OS_KERNEL_H_
#define OS_KERNEL_H_

#define MAX_TASKS 5

typedef struct {
	uint32_t id;
	uint32_t psp_value;
	uint32_t block_count;
	uint8_t current_state;
	uint8_t priority;
	void (*task_handler)(void);
} TCB_t;

#endif /* OS_KERNEL_H_ */
