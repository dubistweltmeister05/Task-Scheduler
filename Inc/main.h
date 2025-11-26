/*
 * main.h
 *
 *  Created on: Nov 22, 2025
 *      Author: HP
 */

#ifndef MAIN_H_
#define MAIN_H_


#define SIZE_TASK_STACK          1024U
#define SIZE_SCHED_STACK         1024U

#define SRAM_START               0x20000000U
#define SIZE_SRAM                ( (128) * (1024))
#define SRAM_END                 ((SRAM_START) + (SIZE_SRAM) )

#define T1_STACK_START           SRAM_END
#define T2_STACK_START           ( (SRAM_END) - (1 * SIZE_TASK_STACK) )
#define T3_STACK_START           ( (SRAM_END) - (2 * SIZE_TASK_STACK) )
#define T4_STACK_START           ( (SRAM_END) - (3 * SIZE_TASK_STACK) )
#define IDLE_STACK_START         ( (SRAM_END) - (4 * SIZE_TASK_STACK) )
#define SCHED_STACK_START        ( (SRAM_END) - (5 * SIZE_TASK_STACK) )

uint32_t TICK_FREQ =1000;
#define HSI_CLOCK				16000000U
#define SYSTICK_TIMER_CLK   	HSI_CLOCK

#define MAX_TASKS 				4
#define dummy_XPSR				0x01000000U

#endif /* MAIN_H_ */
