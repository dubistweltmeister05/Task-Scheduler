/*
 * led.c
 *
 *  Created on: Dec 4, 2025
 *      Author: KshitijVaze
 */
#include<stdint.h>
#include"led.h"

//this is the basic delay function used to blink the damn thing
void delay(uint32_t time) {
	for (volatile int i = 0; i < time; i++) {
		;
	}
}

//this is to initialize the LED pins
void led_init() {
	//Enable the clock for the peripheral
	*pRCC_AHB1ENR |= (1 << 3);

	//configured the modes to be output
	GPIOD->MODER |= (1 << (2 * LED_GREEN));
	GPIOD->MODER |= (1 << (2 * LED_RED));
	GPIOD->MODER |= (1 << (2 * LED_BLUE));
	GPIOD->MODER |= (1 << (2 * LED_ORANGE));

	//No need to specify the OP Type, since the reset state is in OP Push Pull.

	//I want the speed to be very, very fast
	GPIOD->OSPEEDR |= (3 << (2 * LED_GREEN));
	GPIOD->OSPEEDR |= (3 << (2 * LED_RED));
	GPIOD->OSPEEDR |= (3 << (2 * LED_BLUE));
	GPIOD->OSPEEDR |= (3 << (2 * LED_ORANGE));

	//There has to be no pull on the LED pins
	GPIOD->PUPDR &= ~(3 << (2 * LED_GREEN));
	GPIOD->PUPDR &= ~(3 << (2 * LED_RED));
	GPIOD->PUPDR &= ~(3 << (2 * LED_BLUE));
	GPIOD->PUPDR &= ~(3 << (2 * LED_ORANGE));

}
// function to turn on
void led_on(uint8_t led_no) {
	GPIOD->BSRR = (1U << led_no); //Bit set/reset register, it is atomic in nature
}

// function to turn off
void led_off(uint8_t led_no) {
	GPIOD->BSRR = (1U << (led_no + 16));
}
