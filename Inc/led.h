/*
 * led.h
 *
 *  Created on: Dec 4, 2025
 *      Author: KshitijVaze
 */

#ifndef LED_H_
#define LED_H_

//First, we define the pin numbers
#define LED_GREEN  12
#define LED_ORANGE 13
#define LED_RED    14
#define LED_BLUE   15

//then, we make a structure that holds the registers.
typedef struct {
	volatile uint32_t MODER;    // GPIO mode register
	volatile uint32_t OTYPER;   // Output type register
	volatile uint32_t OSPEEDR;  // Output speed register
	volatile uint32_t PUPDR;    // Pull-up/pull-down register
	volatile uint32_t IDR;      // Input data register
	volatile uint32_t ODR;      // Output data register
	volatile uint32_t BSRR;     // Bit set/reset register
	volatile uint32_t LCKR;     // Configuration lock register
	volatile uint32_t AFRL;     // Alternate function low register
	volatile uint32_t AFRH;     // Alternate function high register
} GPIO_RegDef_t;

//this is a pointer to the Bus address that controls the GPIO port
volatile uint32_t *pRCC_AHB1ENR = (volatile uint32_t*) 0x40023830;

//this, is the base address for the GPIO Port on which the
#define GPIOD_BASEADDR   0x40020C00U
#define GPIOD 			 ((GPIO_RegDef_t*)GPIOD_BASEADDR)

#endif /* LED_H_ */
