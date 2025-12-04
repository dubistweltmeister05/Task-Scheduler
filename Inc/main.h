/*
 * main.h
 *
 *  Created on: Nov 30, 2025
 *      Author: HP
 */

#ifndef MAIN_H_
#define MAIN_H_

#define TASK_STACK_SIZE				1024U
#define SCHEDULER_STACK_SIZE		1024U

#define SRAM_START					0x20000000U
#define SRAM_SIZE					(128*1024)
#define SRAM_END					((SRAM_START)+(SRAM_SIZE))

#define TASK_1_STACK_START			(SRAM_END)
#define TASK_2_STACK_START			((SRAM_END)-(1*TASK_STACK_SIZE))
#define TASK_3_STACK_START			((SRAM_END)-(2*TASK_STACK_SIZE))
#define TASK_4_STACK_START			((SRAM_END)-(3*TASK_STACK_SIZE))
#define SCHEDULER_STACK_START		((SRAM_END)-(4*TASK_STACK_SIZE))

#define HSI_CLOCK					16000000U
#define SYSTICK_TIMER_CLOCK			HSI_CLOCK
uint32_t timer_freq = 1000U;
#define MAX_TASKS 4
uint32_t psp_of_tasks[MAX_TASKS] = { TASK_1_STACK_START, TASK_2_STACK_START,
		TASK_3_STACK_START, TASK_4_STACK_START };

#define dummy_xpsr					0x01000000U

uint32_t task_handlers[MAX_TASKS];

void BusFault_Handler(void);
void MemManage_Handler(void);
void HardFault_Handler(void);

uint32_t current_task = 0;
#endif /* MAIN_H_ */
