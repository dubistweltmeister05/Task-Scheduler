# STM32 Task Scheduler

A bare-metal round-robin task scheduler implementation for STM32F407VGTx microcontroller. This project demonstrates a custom task scheduler that manages multiple tasks using manual context switching, stack management, and the SysTick timer.

## 📋 Table of Contents

- [Overview](#overview)
- [Hardware Requirements](#hardware-requirements)
- [Features](#features)
- [Architecture](#architecture)
- [How It Works](#how-it-works)
- [Project Structure](#project-structure)
- [Building and Running](#building-and-running)
- [Configuration](#configuration)
- [Code Explanation](#code-explanation)
- [License](#license)

## 🎯 Overview

This project implements a cooperative round-robin task scheduler for the STM32F407VGTx microcontroller. The scheduler manages 4 independent tasks, each with its own stack space, and switches between them using the SysTick timer interrupt. The implementation is done entirely in bare-metal C and ARM assembly, without using any RTOS framework.

## 🔧 Hardware Requirements

- **Microcontroller**: STM32F407VGTx
  - ARM Cortex-M4 processor
  - 128KB SRAM
  - 1024KB Flash memory
  - 16MHz HSI clock source
- **Development Board**: STM32F407G-DISC1 (or compatible)
- **Debugger**: ST-Link (or compatible)
- **IDE**: STM32CubeIDE

## ✨ Features

- **Round-Robin Scheduling**: Tasks are executed in a circular fashion
- **Manual Context Switching**: Full control over task context save/restore
- **Stack Management**: Each task has its own dedicated stack space (1KB per task)
- **SysTick Timer Integration**: Uses hardware timer for periodic context switches
- **Exception Handling**: Includes handlers for HardFault, MemManage, and BusFault
- **Bare-Metal Implementation**: No RTOS dependencies, pure C and assembly

## 🏗️ Architecture

### Memory Layout

```
SRAM (128KB) - Starting at 0x20000000
├── Task 4 Stack (1KB)    - Highest address
├── Task 3 Stack (1KB)
├── Task 2 Stack (1KB)
├── Task 1 Stack (1KB)
└── Scheduler Stack (1KB)  - Lowest address
```

### Task Management

- **Maximum Tasks**: 4 tasks (configurable via `MAX_TASKS`)
- **Stack Size**: 1KB per task (configurable via `TASK_STACK_SIZE`)
- **Scheduler Stack**: 1KB (configurable via `SCHEDULER_STACK_SIZE`)

### Scheduling Algorithm

The scheduler uses a simple round-robin algorithm:
1. Tasks are executed in order: Task 1 → Task 2 → Task 3 → Task 4 → Task 1 (repeat)
2. Context switch occurs on every SysTick interrupt (default: 1ms)
3. Current task index wraps around using modulo operation

## 🔄 How It Works

1. **Initialization Phase**:
   - Enable processor fault handlers
   - Initialize scheduler stack (MSP)
   - Set up task handler function pointers
   - Initialize each task's stack with proper frame structure
   - Configure SysTick timer for periodic interrupts

2. **Context Switching**:
   - On SysTick interrupt, save current task context (R4-R11 registers)
   - Update current task index (round-robin)
   - Restore next task's context
   - Switch to Process Stack Pointer (PSP)

3. **Task Execution**:
   - Each task runs in an infinite loop
   - Tasks are preempted by SysTick interrupt
   - Context is automatically saved/restored during switches

## 📁 Project Structure

```
task_Scheduler_/
├── Inc/
│   └── main.h              # Header file
├── Src/
│   ├── main.c              # Main application code with scheduler
│   ├── syscalls.c          # System call implementations
│   └── sysmem.c            # Memory management
├── Startup/
│   └── startup_stm32f407vgtx.s  # Startup assembly code
├── Debug/                  # Build artifacts
├── STM32F407VGTX_FLASH.ld  # Flash linker script
├── STM32F407VGTX_RAM.ld    # RAM linker script
└── README.md               # This file
```

## 🚀 Building and Running

### Prerequisites

- STM32CubeIDE installed
- ST-Link drivers installed
- STM32F407G-DISC1 board (or compatible)

### Build Steps

1. Open the project in STM32CubeIDE
2. Clean and build the project:
   - Right-click on project → Clean Project
   - Right-click on project → Build Project
3. Connect your STM32 board via ST-Link
4. Flash the program:
   - Right-click on project → Run As → STM32 MCU C/C++ Application

### Running

After flashing, the scheduler will start automatically. You can observe the task switching behavior through:
- Serial output (if UART is configured)
- Debugger console
- LED indicators (if configured)

## ⚙️ Configuration

### Timer Frequency

Adjust the scheduler tick frequency by modifying:
```c
uint32_t timer_freq = 1000U;  // 1000 Hz = 1ms tick
```

### Number of Tasks

Change the maximum number of tasks:
```c
#define MAX_TASKS 4
```

### Stack Sizes

Modify stack sizes as needed:
```c
#define TASK_STACK_SIZE        1024U
#define SCHEDULER_STACK_SIZE   1024U
```

## 📖 Code Explanation

### Key Functions

- **`init_systick_timer()`**: Configures SysTick timer for periodic interrupts
- **`SysTick_Handler()`**: Interrupt handler that performs context switching
- **`init_task_stack()`**: Sets up initial stack frame for each task
- **`switch_to_psp()`**: Switches from MSP to PSP for task execution
- **`save_psp_value()` / `get_psp_value()`**: Manages task stack pointers
- **`update_next_task()`**: Implements round-robin task selection

### Context Switching Process

1. **Save Context**: Store R4-R11 registers to current task's stack
2. **Update PSP**: Save current PSP value to task array
3. **Select Next Task**: Increment and wrap task index
4. **Restore Context**: Load R4-R11 from next task's stack
5. **Update PSP**: Set PSP to next task's stack pointer

### Stack Frame Structure

Each task's stack is initialized with:
- XPSR (Exception Program Status Register)
- PC (Program Counter) - points to task handler
- LR (Link Register) - return address
- R0-R12, SP - general purpose registers

## ⚠️ Important Notes

- **FPU Warning**: The project may show a warning about FPU initialization. This is expected if FPU is not used.
- **Stack Overflow**: Ensure tasks don't exceed their allocated stack size (1KB)
- **Interrupt Safety**: Critical sections should disable interrupts if needed
- **No Preemption Control**: Tasks cannot voluntarily yield; only SysTick preempts

## 🔍 Debugging

- Use STM32CubeIDE debugger to step through code
- Monitor `current_task` variable to see task switching
- Check `psp_of_tasks[]` array to verify stack pointers
- Enable fault handlers to catch memory violations

## 📝 License

Copyright (c) 2025 STMicroelectronics.
All rights reserved.

This software is licensed under terms that can be found in the LICENSE file in the root directory of this software component. If no LICENSE file comes with this software, it is provided AS-IS.

## 👤 Author

Created by yours truly, inspired by Fastbit EBA on Udemy

## 🔗 References

- [STM32F407 Reference Manual](https://www.st.com/resource/en/reference_manual/rm0090-stm32f407-advanced-armbased-32bit-mcus-stmicroelectronics.pdf)
- [ARM Cortex-M4 Technical Reference Manual](https://developer.arm.com/documentation/ddi0439/b/)

---

**Note**: This is an educational project demonstrating low-level task scheduling concepts. For production applications, consider using established RTOS solutions like FreeRTOS, RT-Thread, or Zephyr.

