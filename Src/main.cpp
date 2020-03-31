/*
 * main.cpp
 *
 *  Created on: 26 Mar 2020
 *      Author: Erick Cabral
 */

#include "stm32H743xx.h"

int main(void) {

	RCC rcc = RCC(RCC_BASEADDRESS);
	rcc.setGPIOxEnable(GPIOB, ENABLE);

	GPIOx gpioB = GPIOx(GPIOB_BASEADDRESS);
	gpioB.setPinMode(PIN_0, MODE_OUTPUT);
	gpioB.setPinType(PIN_0, TYPE_PUSHPULL);
	gpioB.setPinSpeed(PIN_0, SPD_MID);
	gpioB.setPinPUPD(PIN_0, PUPD_PULL_UP);

	gpioB.setPinODR(PIN_0, SET);

	while (1) {

	}
}

